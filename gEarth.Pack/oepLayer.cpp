#include "stdafx.h"
#include "oepLayer.h"
#include "Handle.h"
#include "oepLayerFactory.h"
#include <osgEarth/Map>
#include <msclr\marshal_cppstd.h>  

using namespace msclr::interop;
using namespace gEarthPack;

oepLayer::oepLayer():_handle(NULL)
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
	if (!_handle)
		return NULL;
	return _handle->getValue();
}

String^ gEarthPack::oepLayer::StatusString::get()
{
	osgEarth::Layer* plyr = asoeLayer();
	if (!plyr)
		return "";
	return marshal_as<String^>(plyr->getStatus().toString());
}

bool gEarthPack::oepLayer::IsOK::get()
{
	osgEarth::Layer* plyr = asoeLayer();
	if (!plyr)
		return false;
	return plyr->getStatus().isOK() ? true : false;
}

String^ gEarthPack::oepLayer::Name::get()
{
	osgEarth::Layer* plyr = asoeLayer();
	if (!plyr)
		return "";
	return marshal_as<String^>(plyr->getName());
}

void gEarthPack::oepLayer::Name::set(String^ v)
{
	osgEarth::Layer* plyr = asoeLayer();
	if (!plyr)
		return;
	plyr->setName(marshal_as<std::string>(v));
	NotifyChanged("Name");
}

