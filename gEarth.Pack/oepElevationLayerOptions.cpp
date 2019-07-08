#include "stdafx.h"
#include "oepElevationLayerOptions.h"

using namespace gEarthPack;

oepElevationLayerOptions::oepElevationLayerOptions()
{
	_handle = new osgEarth::ElevationLayerOptions();
}

osgEarth::ElevationLayerOptions* gEarthPack::oepElevationLayerOptions::asoeElevationLayerOptions()
{
	return dynamic_cast<osgEarth::ElevationLayerOptions*>(_handle);
}
