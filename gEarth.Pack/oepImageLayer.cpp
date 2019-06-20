#include "stdafx.h"
#include "oepImageLayer.h"
using namespace gEarthPack;

oepImageLayer::oepImageLayer(oepTileSource^ source)
	:oepTerrainLayer(source)
{
	if (source != nullptr && source->getoeConfigOptions() != NULL)
		_handle->setValue(new osgEarth::ImageLayer(*(source->getoeConfigOptions())));
	else
		_handle->setValue(new osgEarth::ImageLayer());
}

oepImageLayer::oepImageLayer(osgEarth::ImageLayer* layer)
{
	_handle->setValue(layer);
}

osgEarth::ImageLayer* gEarthPack::oepImageLayer::asoeImageLayer()
{
	return dynamic_cast<osgEarth::ImageLayer*>(_handle->getValue());
}
