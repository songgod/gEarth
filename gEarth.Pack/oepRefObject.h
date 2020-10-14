#pragma once
#include "oepObject.h"

namespace gEarthPack
{
	class oepRefHandle
	{
	public:
		oepRefHandle()
		{

		}
		oepRefHandle(osg::Referenced* t)
		{
			_handle = t;
		}

	public:

		osg::Referenced* getValue() { return _handle.get(); }
		const osg::Referenced* getValue() const { return _handle.get(); }
		void setValue(osg::Referenced* v) { _handle = v; }

	private:
		osg::ref_ptr<osg::Referenced> _handle;
	};


	public ref class oepRefObject :
		public oepObject
	{
	public:
		oepRefObject()
		{
			_handle = new oepRefHandle();
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

		osg::Referenced* ref()
		{
			if (_handle)
				return _handle->getValue();
			return NULL;
		}

		template<class T>
		T* as()
		{
			if (_handle)
				return dynamic_cast<T*>(_handle->getValue());
			return NULL;
		}

		void bind(osg::Referenced* v)
		{
			unbind();
			if (_handle)
			{
				_handle->setValue(v);
				if (v != NULL)
					binded();
			}
				
		}

		void unbind()
		{
			if (_handle && _handle->getValue()!=NULL)
			{
				unbinded();
				_handle->setValue(NULL);
			}
		}

	internal:

		virtual void binded(){}
		virtual void unbinded(){}

	protected:

		oepRefHandle* _handle;
	};
}


