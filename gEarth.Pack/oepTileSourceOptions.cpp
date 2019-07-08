#include "stdafx.h"
#include "oepTileSourceOptions.h"
using namespace gEarthPack;

oepTileSourceOptions::oepTileSourceOptions()
{
}

osgEarth::TileSourceOptions* gEarthPack::oepTileSourceOptions::asoeTileSourceOptions()
{
	return dynamic_cast<osgEarth::TileSourceOptions*>(_handle);
}
