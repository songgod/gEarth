#pragma once
#include "oepVisibleLayer.h"
#include "oepTerrainLayerOptions.h"
#include <osgEarth/TerrainLayer>

namespace gEarthPack
{
	public ref class oepTerrainLayer : public oepVisibleLayer
	{
	public:
		oepTerrainLayer();

	public:

		osgEarth::TerrainLayer* asoeTerrainLayer();
	};
}

