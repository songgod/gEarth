#pragma once

#include <osgEarth/Map>
#include "oepLayer.h"
#include "Handle.h"

using namespace System;

namespace gEarthPack 
{
	public ref class oepMap : public oepObject
	{
	public:
		oepMap();
		~oepMap();
		!oepMap();

	public:

		property oepLayers^ Layers
		{
			oepLayers^ get();
		}

	internal:

		void quit();
		osgEarth::Map* getMap();

	private:

		void OnCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e);

	private:

		typedef Handle<osgEarth::Map> MapHandle;
		MapHandle* _handle;
		oepLayers^ _layers;
	};
}
