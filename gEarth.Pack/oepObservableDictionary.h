#pragma once

using namespace System::ComponentModel;
using namespace System::Collections::Generic;
using namespace System::Collections::Specialized;
using namespace System;

namespace gEarthPack
{
	template<typename TKey, typename TValue>
	public ref class oepObservableDictionary : public Dictionary<TKey, TValue>, public INotifyCollectionChanged, public INotifyPropertyChanged
	{
	public:
		oepObservableDictionary()
		{

		}

	public:

		virtual event NotifyCollectionChangedEventHandler^ CollectionChanged;
		virtual event PropertyChangedEventHandler^ PropertyChanged;

	public:

		property KeyCollection^ Keys
		{
			KeyCollection^ get()
			{
				return Dictionary::Keys;
			}
		}

		property ValueCollection^ Values
		{
			ValueCollection^ get()
			{
				return Dictionary::Values;
			}
		}

		property int Count
		{
			int get() new
			{
				return Dictionary::Count;
			}
		}

		property TValue default[TKey]
		{
			TValue get(TKey key) new
			{
				return GetValue(key);
			}
			void set(TKey key, TValue value) new
			{
				SetValue(key, value);
			}
		}

			void Add(TKey key, TValue value) new
		{
			Dictionary::Add(key, value);
			this->OnCollectionChanged(gcnew NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction::Add, this->FindPair(key), _index));
			OnPropertyChanged("Keys");
			OnPropertyChanged("Values");
			OnPropertyChanged("Count");
		}

		void Clear() new
		{
			Dictionary::Clear();
			this->OnCollectionChanged(gcnew NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction::Reset));
			OnPropertyChanged("Keys");
			OnPropertyChanged("Values");
			OnPropertyChanged("Count");
		}

		bool Remove(TKey key) new
		{
			var pair = this->FindPair(key);
			if (Dictionary::Remove(key))
			{
				this.OnCollectionChanged(gcnew NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Remove, pair, _index));
				OnPropertyChanged("Keys");
				OnPropertyChanged("Values");
				OnPropertyChanged("Count");
				return true;
			}
			return false;
		}

	protected:

		void OnCollectionChanged(NotifyCollectionChangedEventArgs^ e)
		{
			this->CollectionChanged(this, e);
		}

		void OnPropertyChanged(String^ propertyName)
		{

			this->PropertyChanged(this, gcnew PropertyChangedEventArgs(propertyName));
		}

	private:

		TValue GetValue(TKey key)
		{
			if (Dictionary::ContainsKey(key))
			{
				TValue v;
				if (Dictionary::TryGetValue(key, v))
					return v;
			}
			return TValue();
		}

		void SetValue(TKey key, TValue value)
		{
			if (Dictionary::ContainsKey(key))
			{
				KeyValuePair<TKey, TValue>^ pair = this->FindPair(key);
				int index = _index;
				this[key] = value;
				KeyValuePair<TKey, TValue>^ newpair = this->FindPair(key);
				this->OnCollectionChanged(gcnew NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction::Replace, newpair, pair, index));
				OnPropertyChanged("Values");
				OnPropertyChanged("Item[]");
			}
			else
			{
				this->Add(key, value);
			}
		}

		KeyValuePair<TKey, TValue>^ FindPair(TKey key)
		{
			_index = 0;
			for each(KeyValuePair<TKey, TValue>^ item in this)
			{
				if (item->Key->Equals(key))
				{
					return item;
				}
				_index++;
			}
			return nullptr;
		}

	private:
		int _index;
	};
}


