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

oepElevationLayer::oepElevationLayer(osgEarth::ElevationLayer* pElevationLayer)
{
	_handle->setValue(pElevationLayer);
}

osgEarth::ElevationLayer * gEarthPack::oepElevationLayer::asoeElevationLayer()
{
	return dynamic_cast<osgEarth::ElevationLayer*>(_handle->getValue());
}



