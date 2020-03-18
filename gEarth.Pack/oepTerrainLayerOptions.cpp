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
	osgEarth::TerrainLayerOptions* to = as<osgEarth::TerrainLayerOptions>();
	if (to != NULL && v != nullptr)
	{
		to->driver() = *(v->as<osgEarth::TileSourceOptions>());
		NotifyChanged("driver");
	}
}
