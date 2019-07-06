// gEarth.Pack.h

#pragma once

#include "viewer.h"
#include "oepMap.h"
#include "oepViewpoint.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace gEarthPack {

	public ref class Render
	{
	public:

		Render();

	public:

		void Start(IntPtr hwnd);
		void End();

	public:

		bool Open(oepMap^ map);
		void Flyto(oepViewpoint^ vp);

	protected:

		Viewer* _viewer;
	};
}
