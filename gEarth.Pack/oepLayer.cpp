#include "stdafx.h"
#include "oepLayer.h"
#include "oepHandle.h"
#include "oepLayerFactory.h"

using namespace msclr::interop;
using namespace gEarthPack;

oepLayer::oepLayer():_handle(NULL)
{
	_handle = new LayerHandle();
}

oepLayer::~oepLayer()
{
	quit();
}

oepLayer::!oepLayer()
{
	quit();
}

void oepLayer::quit()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

osgEarth::Layer* oepLayer::asoeLayer()
{
	if (!_handle)
		return NULL;
	return _handle->getValue();
}

String^ oepLayer::StatusString::get()
{
	osgEarth::Layer* plyr = asoeLayer();
	if (!plyr)
		return "";
	return marshal_as<String^>(plyr->getStatus().toString());
}

bool oepLayer::IsOK::get()
{
	osgEarth::Layer* plyr = asoeLayer();
	if (!plyr)
		return false;
	return plyr->getStatus().isOK() ? true : false;
}

String^ oepLayer::Name::get()
{
	osgEarth::Layer* plyr = asoeLayer();
	if (!plyr)
		return "";
	return marshal_as<String^>(plyr->getName());
}

void oepLayer::Name::set(String^ v)
{
	osgEarth::Layer* plyr = asoeLayer();
	if (!plyr)
		return;
	plyr->setName(marshal_as<std::string>(v));
	NotifyChanged("Name");
}