#pragma once
#include "oepObject.h"

namespace gEarthPack
{
	template<class T>
	public ref class oepValObject :
		public oepObject
	{
	public:
		oepValObject():_handle(NULL)
		{

		}
		!oepValObject()
		{
			if(_handle)
				delete _handle;
		}
		~oepValObject()
		{
			this->!oepValObject();
		}

	internal:

		T* val() { return _handle; }

		template<class T1>
		T1* as()
		{
			if (_handle)
				return dynamic_cast<T1*>(_handle);
			return NULL;
		}

	protected:

		T* _handle;
	};

}