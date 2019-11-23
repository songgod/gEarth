#include "stdafx.h"
#include "oepFeatureElevationSourceOptions.h"
using namespace gEarthPack;

oepFeatureElevationSourceOptions::oepFeatureElevationSourceOptions()
{
	setVal(new osgEarth::Drivers::FeatureElevationOptions());
}