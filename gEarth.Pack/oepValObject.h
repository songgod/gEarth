#pragma once
#include "oepObject.h"

namespace gEarthPack
{
	template<class T>
	public ref class oepValObject :
		public oepObject
	{
	public:
		oepValObject() : _ownhandle(true), _handle(NULL)
		{

		}

		!oepValObject()
		{
			if (_handle && _ownhandle)
				delete _handle;
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

		T* val() { return (T*)_handle; }

		template<class T1>
		T1* as()
		{
			if (_handle)
				return dynamic_cast<T1*>(_handle);
			return NULL;
		}

		template<class T1>
		void bind(osgEarth::optional<T1>& handle, bool own)
		{
			if (!handle.isSet())
			{
				handle = T1();
			}
			T* h = dynamic_cast<T*>(&(handle.mutable_value()));
			if (!h)
				return;
			bind(h, own);
		}

		void bind(osgEarth::optional<T>& handle, bool own)
		{
			if (!handle.isSet())
			{
				handle = T();
			}
			bind(&(handle.mutable_value()), own);
		}

		void bind(T* handle, bool own)
		{
			if (handle == _handle && _ownhandle)
				return;
			if (_handle != NULL && handle != _handle && _ownhandle)
			{
				delete _handle;
				_handle = NULL;
			}
			_handle = handle;
			_ownhandle = own;
			if (_handle != NULL)
				binded();
			else
				unbinded();
		}

		void unbind()
		{
			bind(NULL,true);
		}

	internal:

		virtual void binded(){}
		virtual void unbinded(){}

	protected:

		T* _handle;
		bool _ownhandle;
	};
}