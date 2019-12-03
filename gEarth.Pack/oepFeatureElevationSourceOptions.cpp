#include "stdafx.h"
#include "oepFeatureElevationSourceOptions.h"
using namespace gEarthPack;

oepFeatureElevationSourceOptions::oepFeatureElevationSourceOptions()
{
	bind(new osgEarth::Drivers::FeatureElevationOptions(),true);
}