#pragma once
#include "oepTerrainLayer.h"
#include "oepImageLayerOptions.h"
#include "oepColorFilter.h"
#include <osgEarth/ImageLayer>

namespace gEarthPack
{
	public ref class oepImageLayer : public oepTerrainLayer
	{
	public:
		oepImageLayer(oepImageLayerOptions^ imagelayeroptions);

	public:

		property oepColorFilters^ ColorFilters
		{
			oepColorFilters^ get();
		}

	internal:

		osgEarth::ImageLayer* asoeImageLayer();
		oepImageLayer(osgEarth::ImageLayer* layer);

	private:

		void OnColorFiltersCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e);

	private:

		oepColorFilters^ _colorfilters;
	};
}

