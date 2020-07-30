#pragma once

#include "oepObservableDictionary.h"

namespace gEarthPack
{
	template<typename MKey, typename MValue, typename LKey, typename LValue>
	public ref class oepValMap : public oepObservableDictionary<MKey, MValue>
	{
	public:
		oepValMap() : _bOwn(true)
		{
			_map = new std::map<LKey,LValue>();
			this->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepValMap::OnMTCollectionChanged);
		}

		!oepValMap()
		{
			if (_map && _bOwn)
			{
				delete _map;
				_map = NULL;
			}
		}

		virtual ~oepValMap()
		{
			this->!oepValMap();
		}

		property bool Valid
		{
			bool get() { return _map != NULL; }
		}



	internal:

		std::map<LKey, LValue>* Val()
		{
			return _map;
		}

		void bind(std::map<LKey, LValue>* handle, bool own)
		{
			if (_map && _bOwn)
			{
				delete _map;
				_map = NULL;
			}
			_map = handle;
			_bOwn = own;
			this->CollectionChanged -= gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepValMap::OnMTCollectionChanged);
			this->Clear();
			if (handle != NULL)
			{
				std::map<LKey, LValue>& tmp = *handle;
				for (std::map<LKey, LValue>::iterator iter = tmp.begin(); iter!=tmp.end(); iter++)
				{
					MValue tmpop = this->NewMValue();
					tmpop->bind(&(iter->second), false);
					this[this->LKey2MKey(iter->first)] = tmpop;
				}
			}
			this->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepValMap::OnMTCollectionChanged);
		}

		void unbind()
		{
			bind(NULL, true);
		}

	internal:

		virtual MValue NewMValue() { throw gcnew NotImplementedException(); }
		virtual MKey LKey2MKey(LKey key) { throw gcnew NotImplementedException(); }
		virtual LKey MKey2LKey(MKey key) { throw gcnew NotImplementedException(); }

	private:

		void OnMTCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e)
		{
			_map->clear();
			KeyCollection^ keys = Keys;
			for each (MKey key in keys)
			{
				LKey lkey = this->MKey2LKey(key);
				MValue mv = this[key];
				(*_map)[lkey] = *(mv->as<LValue>());
				mv->bind(&((*_map)[lkey]), false);
			}
		}

	protected:

		std::map<LKey,LValue> *_map;
		bool _bOwn;
	};
}

