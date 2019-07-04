#pragma once
#include "oepTerrainLayer.h"
#include "oepColorFilter.h"
#include <osgEarth/ImageLayer>

namespace gEarthPack
{
	public ref class oepImageLayer : public oepTerrainLayer
	{
	public:
		oepImageLayer(oepTileSource^ source);

	public:

		property oepColorFilters^ ColorFilters
		{
			oepColorFilters^ get();
		}

	public:

		osgEarth::ImageLayer* asoeImageLayer();

	internal:

		oepImageLayer(osgEarth::ImageLayer* layer);

	private:

		void OnColorFiltersCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e);

	private:

		oepColorFilters^ _colorfilters;
	};
}

