#include "stdafx.h"
#include "oepLayer.h"
#include "oepLayerFactory.h"


using namespace gEarthPack;

oepLayer::oepLayer()
{

}

String^ oepLayer::StatusString::get()
{
	osgEarth::Layer* plyr = as<osgEarth::Layer>();
	if (!plyr)
		return "";
	return Str2Cli(plyr->getStatus().toString());
}

bool oepLayer::IsOK::get()
{
	osgEarth::Layer* plyr = as<osgEarth::Layer>();
	if (!plyr)
		return false;
	return plyr->getStatus().isOK() ? true : false;
}

String^ oepLayer::Name::get()
{
	osgEarth::Layer* plyr = as<osgEarth::Layer>();
	if (!plyr)
		return "";
	return Str2Cli(plyr->getName());
}

void oepLayer::Name::set(String^ v)
{
	osgEarth::Layer* plyr = as<osgEarth::Layer>();
	if (!plyr)
		return;
	plyr->setName(Str2Std(v));
	NotifyChanged("Name");
}