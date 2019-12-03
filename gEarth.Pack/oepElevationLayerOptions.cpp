#include "stdafx.h"
#include "oepElevationLayerOptions.h"

using namespace gEarthPack;

oepElevationLayerOptions::oepElevationLayerOptions()
{
	bind(new osgEarth::ElevationLayerOptions(),true);
}
