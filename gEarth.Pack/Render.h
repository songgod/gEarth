// gEarth.Pack.h

#pragma once

#include "viewer.h"

using namespace System;

namespace gEarthPack {

	public ref class Render
	{
	public:

		Render();
		!Render();
		~Render();
		// TODO: Add your methods for this class here.
	public:

		void Start(IntPtr hwnd);
		void End();

	public:

		bool Open(String^ url);

	protected:

		Viewer* _viewer;
	};
}
