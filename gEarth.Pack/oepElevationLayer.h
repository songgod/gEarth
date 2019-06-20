#pragma once
#include "oepTerrainLayer.h"
#include <osgEarth/ElevationLayer>

namespace gEarthPack
{
	public ref class oepElevationLayer : public oepTerrainLayer
	{
	public:
		oepElevationLayer(oepTileSource^ source);

	public:

		osgEarth::ElevationLayer* asoeElevationLayer();

	internal:

		oepElevationLayer(osgEarth::ElevationLayer* pElevationLayer);
	};
}

