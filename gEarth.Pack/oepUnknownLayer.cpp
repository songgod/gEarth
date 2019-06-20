#include "stdafx.h"
#include "oepUnknownLayer.h"

using namespace gEarthPack;

oepUnknownLayer::oepUnknownLayer()
{
}

oepUnknownLayer::oepUnknownLayer(osgEarth::Layer* layer)
{
	_handle->setValue(layer);
}