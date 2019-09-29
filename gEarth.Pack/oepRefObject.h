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
			_handle = new RefHandle();
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

	protected:

		typedef oepHandle<T> RefHandle;
		RefHandle* _handle;
	};
}


