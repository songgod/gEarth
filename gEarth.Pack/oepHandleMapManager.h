#pragma once

using namespace System::Collections::Generic;
using namespace System;

namespace gEarthPack
{
	public ref class oepHandleMapManager
	{
		typedef Dictionary<IntPtr, Object^> HandleMap;

	public:
		static oepHandleMapManager();

	public:

		static void registerHandle(void* p, Object^ obj);

		static void unRegisterHandle(void* p);

		static void unRegisterHandle(Object^ obj);

		static Object^ getHandle(void* p);

		template<class T>
		static T^ getHandle(void* p)
		{
			return dynamic_cast<T^>(getHandle(p));
		}

	private:

		static HandleMap^ _handlemap;
	};
}


