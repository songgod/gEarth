#pragma once

namespace gEarthPack
{
	template<class T>
	class oepHandle
	{
	public:
		oepHandle()
		{
			
		}
		oepHandle(T* t)
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