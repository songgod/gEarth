#include "stdafx.h"
#include "oepTileSourceOptions.h"
using namespace gEarthPack;

oepTileSourceOptions::oepTileSourceOptions()
{
}

osgEarth::TileSourceOptions* oepTileSourceOptions::asoeTileSourceOptions()
{
	return dynamic_cast<osgEarth::TileSourceOptions*>(_handle);
}
