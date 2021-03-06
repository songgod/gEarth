#pragma once
#include "oepTerrainLayer.h"
#include "oepImageLayerOptions.h"
#include "oepColorFilter.h"

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

		oepImageLayer(osgEarth::ImageLayer* layer);

	private:

		void OnColorFiltersCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e);

	private:

		oepColorFilters^ _colorfilters;
	};
}

