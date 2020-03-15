// gEarth.Pack.h

#pragma once

#include "oepMap.h"
#include "oepVector.h"
#include "oepViewpoint.h"
#include "oepEventHandler.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace gEarthPack {
	class Viewer;
	ref class oepRender;

	public ref class oepRender : public oepNotify
	{
	public:

		oepRender();

	public:

		property oepViewpoint^ Viewpoint
		{
			oepViewpoint^ get();
			void set(oepViewpoint^ v);
		}

		property oepEventHandlers^ Handlers
		{
			oepEventHandlers^ get();
		}

	public:

		void Start(IntPtr hwnd);
		void End();

	public:

		bool Open(oepMap^ map);

	protected:

		void OnHandlersCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e);

	internal:

		Viewer* _viewer;
		oepEventHandlers^ _handlers;
		oepVec3f _mousecoord;
	};
}
