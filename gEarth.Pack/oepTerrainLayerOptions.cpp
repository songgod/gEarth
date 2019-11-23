#include "stdafx.h"
#include "oepTerrainLayerOptions.h"

using namespace gEarthPack;
oepTerrainLayerOptions::oepTerrainLayerOptions() : _driver(nullptr)
{
}

oepTileSourceOptions^ oepTerrainLayerOptions::driver::get()
{
	return _driver;
}

void oepTerrainLayerOptions::driver::set(oepTileSourceOptions^ v)
{
	_driver = v;
	osgEarth::TerrainLayerOptions* to = as<osgEarth::TerrainLayerOptions>();
	if (to != NULL)
	{
		to->driver() = *(_driver->as<osgEarth::TileSourceOptions>());
	}
}
