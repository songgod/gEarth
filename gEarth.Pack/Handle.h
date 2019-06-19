#pragma once
#include <osg/ref_ptr>

namespace gEarthPack
{
	template<class T>
	class Handle
	{
	public:
		Handle()
		{
			
		}
		Handle(T* t)
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
}