#include "stdafx.h"
#include "oepFeatureModelLayerOptions.h"
#include <osgEarthFeatures/FeatureModelLayer>

using namespace gEarthPack;

oepFeatureModelLayerOptions::oepFeatureModelLayerOptions()
{
	setVal(new osgEarth::Features::FeatureModelLayerOptions());
}

gEarthPack::oepFeatureSourceOptions^ gEarthPack::oepFeatureModelLayerOptions::driver::get()
{
	return _driver;
}

void gEarthPack::oepFeatureModelLayerOptions::driver::set(oepFeatureSourceOptions^ v)
{
	_driver = v;
	osgEarth::Features::FeatureModelLayerOptions* to = as<osgEarth::Features::FeatureModelLayerOptions>();
	if (to != NULL)
	{
		to->featureSource() = *(_driver->as<osgEarth::Features::FeatureSourceOptions>());
	}
}
