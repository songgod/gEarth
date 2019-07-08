#pragma once
#include "oepTerrainLayerOptions.h"
#include <osgEarth/ElevationLayer>

namespace gEarthPack
{
	public ref class oepElevationLayerOptions :
		public oepTerrainLayerOptions
	{
	public:
		oepElevationLayerOptions();

	internal:

		osgEarth::ElevationLayerOptions* asoeElevationLayerOptions();
	};
}
