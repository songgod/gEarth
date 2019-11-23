#include "stdafx.h"
#include "oepModelLayerOptions.h"
#include <osgEarth/ModelLayer>

using namespace gEarthPack;

oepModelLayerOptions::oepModelLayerOptions()
{
	setVal(new osgEarth::ModelLayerOptions());
}

gEarthPack::oepModelSourceOptions^ gEarthPack::oepModelLayerOptions::driver::get()
{
	return _driver;
}

void gEarthPack::oepModelLayerOptions::driver::set(oepModelSourceOptions^ v)
{
	_driver = v;
	osgEarth::ModelLayerOptions* to = as<osgEarth::ModelLayerOptions>();
	if (to != NULL)
	{
		to->driver() = *(_driver->as<osgEarth::ModelSourceOptions>());
	}
}
