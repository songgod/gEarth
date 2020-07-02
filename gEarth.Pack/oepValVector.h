#pragma once

using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	template<typename MT, typename LT>
	public ref class oepValVector : public ObservableCollection<MT^>
	{
	public:
		oepValVector() :_bOwn(true)
		{
			_vector = new std::vector<LT>();
			this->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepValVector::OnMTCollectionChanged);
		}

		!oepValVector()
		{
			if (_vector && _bOwn)
			{
				delete _vector;
				_vector = NULL;
			}
		}

		virtual ~oepValVector()
		{
			this->!oepValVector();
		}

		property bool Valid
		{
			bool get() { return _vector != NULL; }
		}

	internal:

		std::vector<LT> *Val() { return _vector; }

		void bind(std::vector<LT>* handle, bool own)
		{
			if (_vector && _bOwn)
			{
				delete _vector;
				_vector = NULL;
			}
			_vector = handle;
			_bOwn = own;
			this->CollectionChanged -= gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepValVector::OnMTCollectionChanged);
			this->Clear();
			if (handle != NULL)
			{
				std::vector<LT>& tmp = *handle;
				for (size_t i = 0; i < tmp.size(); i++)
				{
					MT^ tmpop = gcnew MT();
					tmpop->bind(&(tmp[i]),false);
					this->Add(tmpop);
				}
			}
			this->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepValVector::OnMTCollectionChanged);
		}

		void unbind()
		{
			bind(NULL, true);
		}

	private:

		void OnMTCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e)
		{
			_vector->resize(Count);
			for (int i = 0; i < Count; i++)
			{
				(*_vector)[i] = *(this[i]->as<LT>());
				this[i]->bind(&((*_vector)[i]), false);
			}
		}

	protected:

		std::vector<LT> *_vector;
		bool _bOwn;
	};

}