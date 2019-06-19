#include "stdafx.h"
#include "oepElevationLayer.h"
using namespace gEarthPack;

oepElevationLayer::oepElevationLayer(oepTileSource^ source)
	:oepTerrainLayer(source)
{
	if (source != nullptr && source->getoeConfigOptions() != NULL)
		_handle->setValue(new osgEarth::ElevationLayer(*(source->getoeConfigOptions())));
	else
		_handle->setValue(new osgEarth::ElevationLayer());
}

osgEarth::ElevationLayer * gEarthPack::oepElevationLayer::asoeElevationLayer()
{
	return dynamic_cast<osgEarth::ElevationLayer*>(_handle->getValue());
}


