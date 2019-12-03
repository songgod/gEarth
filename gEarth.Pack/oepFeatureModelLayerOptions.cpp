#include "stdafx.h"
#include "oepFeatureModelLayerOptions.h"
#include <osgEarthFeatures/FeatureModelLayer>

using namespace gEarthPack;
using namespace osgEarth::Features;

oepFeatureModelLayerOptions::oepFeatureModelLayerOptions()
{
	bind(new FeatureModelLayerOptions(),true);
}

void gEarthPack::oepFeatureModelLayerOptions::binded()
{
	_driver = gcnew oepFeatureSourceOptions();
	_driver->bind(&(as<FeatureModelLayerOptions>()->featureSource().mutable_value()),false);
}

void gEarthPack::oepFeatureModelLayerOptions::unbinded()
{
	_driver->unbind();
}

gEarthPack::oepFeatureSourceOptions^ gEarthPack::oepFeatureModelLayerOptions::driver::get()
{
	return _driver;
}

void gEarthPack::oepFeatureModelLayerOptions::driver::set(oepFeatureSourceOptions^ v)
{
	_driver = v;
	FeatureSourceOptions &fso = as<FeatureModelLayerOptions>()->featureSource().mutable_value();
	_driver->getVal(fso);
	_driver->bind(&fso, false);
}
