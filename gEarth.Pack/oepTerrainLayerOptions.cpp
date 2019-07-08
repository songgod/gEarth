#include "stdafx.h"
#include "oepTerrainLayerOptions.h"

using namespace gEarthPack;
oepTerrainLayerOptions::oepTerrainLayerOptions() : _driver(nullptr)
{
}

osgEarth::TerrainLayerOptions* gEarthPack::oepTerrainLayerOptions::asoeTerrainLayerOptions()
{
	return dynamic_cast<osgEarth::TerrainLayerOptions*>(_handle);
}

gEarthPack::oepTileSourceOptions^ gEarthPack::oepTerrainLayerOptions::driver::get()
{
	return _driver;
}

void gEarthPack::oepTerrainLayerOptions::driver::set(oepTileSourceOptions^ v)
{
	_driver = v;
	osgEarth::TerrainLayerOptions* to = asoeTerrainLayerOptions();
	if (to != NULL)
	{
		to->driver() = *(_driver->asoeTileSourceOptions());
	}
}
