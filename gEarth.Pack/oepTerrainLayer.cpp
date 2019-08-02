#include "stdafx.h"
#include "oepTerrainLayer.h"

using namespace gEarthPack;

oepTerrainLayer::oepTerrainLayer()
{
}

osgEarth::TerrainLayer* oepTerrainLayer::asoeTerrainLayer()
{
	return dynamic_cast<osgEarth::TerrainLayer*>(_handle->getValue());
}
