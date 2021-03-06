#pragma once
#include "oepExtension.h"
#include "oepViewpoint.h"

namespace gEarthPack
{
	public ref class oepViewpointsExtension :
		public oepExtension
	{
	public:
		oepViewpointsExtension();

	public:

		property oepViewPoints^ ViewPoints
		{
			oepViewPoints^ get();
		}

	internal:
		oepViewpointsExtension(osgEarth::Extension* ext);

	private:

		void init();
		void OnViewpointsCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e);

	private:

		oepViewPoints^ _viewpoints;
	};
}


