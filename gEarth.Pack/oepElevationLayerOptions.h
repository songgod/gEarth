#pragma once
#include "oepTerrainLayerOptions.h"

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
