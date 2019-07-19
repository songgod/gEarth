// gEarth.Pack.h

#pragma once

#include "viewer.h"
#include "oepMap.h"
#include "oepViewpoint.h"
#include "oepEventHandler.h"
#include "oepAnimationPath.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace gEarthPack {

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
		void PlayPath(oepAnimationPath^ path);

	protected:

		void OnHandlersCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e);

	internal:

		Viewer* _viewer;
		oepEventHandlers^ _handlers;
	};
}
