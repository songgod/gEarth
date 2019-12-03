#pragma once
#include "oepObject.h"
#include "oepHandle.h"

namespace gEarthPack
{
	template<class T>
	public ref class oepRefObject :
		public oepObject
	{
	public:
		oepRefObject()
		{
			_handle = new oepRefHandle<T>();
		}

		~oepRefObject()
		{
			this->!oepRefObject();
		}

		!oepRefObject()
		{
			if (_handle)
			{
				delete _handle;
			}
		}

	internal:

		T* ref()
		{
			if (_handle)
				return _handle->getValue();
			return NULL;
		}

		template<class T1>
		T1* as()
		{
			if (_handle)
				return dynamic_cast<T1*>(_handle->getValue());
			return NULL;
		}

		void bind(T* v)
		{
			if (_handle)
			{
				_handle->setValue(v);
				if (v != NULL)
					binded();
				else
					unbinded();
			}
				
		}

		void unbind()
		{
			bind(NULL);
		}

	internal:

		virtual void binded(){}
		virtual void unbinded(){}

	protected:

		oepRefHandle<T>* _handle;
	};
}


