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

	internal:

		void getVal(std::vector<LT>& l)
		{
			l = *_vector;
		}

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
			std::vector<LT>* pVal = _vector;
			if (pVal == NULL)
				return;
			std::vector<LT> stdvector(Count);
			for (int i = 0; i < Count; i++)
			{
				this[i]->getVal(stdvector[i]);
			}

			*pVal = stdvector;
			for (int i = 0; i < Count; i++)
			{
				this[i]->bind(&((*pVal)[i]),false);
			}
		}

	protected:

		std::vector<LT> *_vector;
		bool _bOwn;
	};

}