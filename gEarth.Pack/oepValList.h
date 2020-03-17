#pragma once
#include "oepValObject.h"

using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	template<typename MT, typename LT>
	public ref class oepValList : public ObservableCollection<MT^>
	{
	public:
		oepValList() :_bOwn(true)
		{
			_list = new std::list<LT>();
			this->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepValList::OnMTCollectionChanged);
		}

		!oepValList()
		{
			if (_list && _bOwn)
			{
				delete _list;
				_list = NULL;
			}
		}

		virtual ~oepValList()
		{
			this->!oepValList();
		}

	public:

		property bool Valid
		{
			bool get() { return _list != NULL; }
		}

	internal:

		std::list<LT> *Val()
		{
			return _list;
		}

		void bind(std::list<LT>* handle, bool own)
		{
			if (_list && _bOwn)
			{
				delete _list;
				_list = NULL;
			}
			_list = handle;
			_bOwn = own;
			this->CollectionChanged -= gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepValList::OnMTCollectionChanged);
			this->Clear();
			if (handle != NULL)
			{
				for (std::list<LT>::iterator iter = handle->begin(); iter != handle->end(); iter++)
				{
					MT^ tmpop = gcnew MT();
					tmpop->bind(&(*iter),false);
					this->Add(tmpop);
				}
			}
			this->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepValList::OnMTCollectionChanged);
		}

		void unbind()
		{
			bind(NULL, true);
		}

	private:

		void OnMTCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e)
		{
			_list->resize(Count);

			int i = 0;
			for (std::list<LT>::iterator iter = _list->begin(); iter != _list->end(); iter++)
			{
				(*iter) = *(this[i]->val());
				this[i]->bind(&(*iter), false);
				i++;
			}
		}

	protected:

		std::list<LT> *_list;
		bool _bOwn;
	};
}

