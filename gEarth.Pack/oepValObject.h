#pragma once
#include "oepObject.h"

namespace gEarthPack
{
	public ref class oepValObject :
		public oepObject
	{
	public:
		oepValObject() : _ownhandle(true), _handle(NULL)
		{

		}

		!oepValObject()
		{
			if(_handle && _ownhandle)
				delelehandle();
		}

		virtual ~oepValObject()
		{
			this->!oepValObject();
		}

	public:

		property bool Valid
		{
			bool get() { return _handle != NULL; }
		}

	internal:

		void* val() { return _handle; }

		void bind(void* handle, bool own)
		{
			if (handle == _handle)
			{
				if (_ownhandle != own)
				{
					throw gcnew System::Exception("own not equal internal own");
				}
				return;
			}
				
			unbind();
			_handle = handle;
			_ownhandle = own;
			if (_handle != NULL)
				binded();
		}

		void unbind()
		{
			if (_handle != NULL && _ownhandle)
			{
				unbinded();
				delelehandle();
			}
		}

		template<class T>
		T* as()
		{
			if (_handle)
				return static_cast<T*>(_handle);
			return NULL;
		}

		template<class T>
		void del()
		{
			if (_handle && _ownhandle)
			{
				delete (T*)_handle;
				_handle = NULL;
			}
		}

		template<class T>
		void bind(osgEarth::optional<T>& op)
		{
			if (op.isSet())
				op.mutable_value() = T();
			bind(&(op.mutable_value()), false);
		}

	internal:

		virtual void binded(){}
		virtual void unbinded(){}
		virtual void delelehandle()
		{
			if (_handle != NULL)
				throw gcnew System::NotImplementedException();
		}

	protected:

		void* _handle;
		bool _ownhandle;
	};
}