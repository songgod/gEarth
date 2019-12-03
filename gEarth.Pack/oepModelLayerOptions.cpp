#include "stdafx.h"
#include "oepModelLayerOptions.h"
#include <osgEarth/ModelLayer>

using namespace gEarthPack;
using namespace osgEarth;

oepModelLayerOptions::oepModelLayerOptions()
{
	bind(new osgEarth::ModelLayerOptions(),true);
}

void gEarthPack::oepModelLayerOptions::binded()
{
	_driver = gcnew oepModelSourceOptions();
	_driver->bind(&(as<ModelLayerOptions>()->driver().mutable_value()), false);
}

void gEarthPack::oepModelLayerOptions::unbinded()
{
	_driver->unbind();
}

gEarthPack::oepModelSourceOptions^ gEarthPack::oepModelLayerOptions::driver::get()
{
	return _driver;
}

void gEarthPack::oepModelLayerOptions::driver::set(oepModelSourceOptions^ v)
{
	_driver = v;
	ModelSourceOptions &mso = as<ModelLayerOptions>()->driver().mutable_value();
	_driver->getVal(mso);
	_driver->bind(&mso, false);
}
