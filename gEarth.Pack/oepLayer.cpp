#include "stdafx.h"
#include "oepLayer.h"
#include "oepHandle.h"
#include "oepLayerFactory.h"

using namespace msclr::interop;
using namespace gEarthPack;

oepLayer::oepLayer()
{

}

String^ oepLayer::StatusString::get()
{
	osgEarth::Layer* plyr = ref();
	if (!plyr)
		return "";
	return marshal_as<String^>(plyr->getStatus().toString());
}

bool oepLayer::IsOK::get()
{
	osgEarth::Layer* plyr = ref();
	if (!plyr)
		return false;
	return plyr->getStatus().isOK() ? true : false;
}

String^ oepLayer::Name::get()
{
	osgEarth::Layer* plyr = ref();
	if (!plyr)
		return "";
	return marshal_as<String^>(plyr->getName());
}

void oepLayer::Name::set(String^ v)
{
	osgEarth::Layer* plyr = ref();
	if (!plyr)
		return;
	plyr->setName(marshal_as<std::string>(v));
	NotifyChanged("Name");
}