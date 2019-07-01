#include "stdafx.h"
#include "oepLayer.h"
#include "Handle.h"
#include "oepLayerFactory.h"
#include <osgEarth/Map>
#include <msclr\marshal_cppstd.h>  

using namespace msclr::interop;
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

	for (unsigned int i = 0; i < pMap->getNumLayers(); i++)
	{
		osgEarth::Layer* pLayer = pMap->getLayerAt(i);
		std::string type = pLayer->options().getConfig().key();
		oepLayer^ layer = oepLayerFactory::creatorLayer(marshal_as<String^>(type), IntPtr(pLayer));
		Add(layer);
	}
}

String^ gEarthPack::oepLayer::StatusString::get()
{
	return marshal_as<String^>(asoeLayer()->getStatus().toString());
}

bool gEarthPack::oepLayer::IsOK::get()
{
	return asoeLayer()->getStatus().isOK() ? true : false;
}
