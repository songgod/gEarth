#pragma once
#include "oepObject.h"

namespace gEarthPack
{
	template<class T>
	class oepRefHandle
	{
	public:
		oepRefHandle()
		{

		}
		oepRefHandle(T* t)
		{
			_handle = t;
		}

	public:

		T* getValue() { return _handle; }
		const T* getValue() const { return _handle; }
		void setValue(T* v) { _handle = v; }

	private:
		osg::ref_ptr<T> _handle;
	};

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


