#pragma once

using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	template<typename MT, typename LT>
	public ref class oepValMap : public ObservableCollection<MT^>
	{
	public:
		oepValMap() : _bOwn(true)
		{
			_map = new std::map<std::string,LT>();
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

	internal:

		void getVal(std::map<std::string, LT>& l)
		{
			l = *_map;
		}

		void bind(std::map<std::string, LT>* handle, bool own)
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
				std::map<std::string, LT>& tmp = *handle;
				for (std::map<std::string,LT>::iterator iter = tmp.begin(); iter!=tmp.end(); iter++)
				{
					MT^ tmpop = gcnew MT();
					tmpop->bind(&(iter->second), false);
					this->Add(tmpop);
				}
			}
			this->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepValMap::OnMTCollectionChanged);
		}

		void unbind()
		{
			bind(NULL, true);
		}

	private:

		void OnMTCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e)
		{
			std::map<std::string, LT>* pVal = _map;
			if (pVal == NULL)
				return;
			std::map<std::string, LT> stdmap;
			for (int i = 0; i < Count; i++)
			{
				LT lt;
				this[i]->getVal(lt);
				stdmap[lt.getName()] = lt;
			}

			*pVal = stdmap;
			std::map<std::string, LT>& tmp = *pVal;
			int i = 0;
			for (std::map<std::string, LT>::iterator iter = tmp.begin(); iter != tmp.end(); iter++)
			{
				this[i]->bind(&(iter->second), false);
				i++;
			}
		}

	protected:

		std::map<std::string,LT> *_map;
		bool _bOwn;
	};
}

