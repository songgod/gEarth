#pragma once
#include "oepTerrainLayerOptions.h"
#include <osgEarth/ImageLayer>

namespace gEarthPack
{
	public ref class oepImageLayerOptions :
		public oepTerrainLayerOptions
	{
	public:
		oepImageLayerOptions();

	internal:

		osgEarth::ImageLayerOptions* asoeImageLayerOptions();
	};
}
