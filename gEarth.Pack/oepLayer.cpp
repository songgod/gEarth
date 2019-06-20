#include "stdafx.h"
#include "oepLayer.h"
#include "Handle.h"

using namespace gEarthPack;
oepLayer::oepLayer()
{
	_handle = new LayerHandle();
}

gEarthPack::oepLayer::~oepLayer()
{
	quit();
}

gEarthPack::oepLayer::!oepLayer()
{
	quit();
}

void gEarthPack::oepLayer::quit()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

osgEarth::Layer* gEarthPack::oepLayer::asoeLayer()
{
	return _handle->getValue();
}

void gEarthPack::oepLayers::init(osgEarth::Map* pMap)
{
	if (!pMap)
		return;
}
