// gEarth.Pack.h

#pragma once

#include "viewer.h"
#include "oepMap.h"
#include "oepVector.h"
#include "oepViewpoint.h"
#include "oepEventHandler.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace gEarthPack {

	ref class Render;
	public delegate void MouseMoveEvent(Render^, oepVec3f);

	public ref class Render : public oepNotify
	{
	public:

		Render();

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

	public:

		event MouseMoveEvent^ OnMouseMove;
		void FireMoveEvent(oepVec3f p);

	protected:

		void InitEvents();
		void OnHandlersCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e);

	internal:

		Viewer* _viewer;
		oepEventHandlers^ _handlers;
		oepVec3f _mousecoord;
	};
}
