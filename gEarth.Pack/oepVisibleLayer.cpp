#include "stdafx.h"
#include "oepVisibleLayer.h"

using namespace gEarthPack;
oepVisibleLayer::oepVisibleLayer()
{
}

osgEarth::VisibleLayer* gEarthPack::oepVisibleLayer::asoeVisibleLayer()
{
	return dynamic_cast<osgEarth::VisibleLayer*>(_handle->getValue());
}
