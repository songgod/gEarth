#pragma once
#include "oepTerrainLayer.h"
#include "oepElevationLayerOptions.h"

namespace gEarthPack
{
	public ref class oepElevationLayer : public oepTerrainLayer
	{
	public:
		oepElevationLayer(oepElevationLayerOptions^ elevationlayeroptions);

	internal:

		oepElevationLayer(osgEarth::ElevationLayer* pElevationLayer);
	};
}

