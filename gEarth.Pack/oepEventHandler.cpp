#include "stdafx.h"
#include "oepEventHandler.h"


using namespace gEarthPack;

oepEventHandler::oepEventHandler() : _keep(false)
{
	
}

String^ oepEventHandler::Name::get()
{
	osgGA::EventHandler* evh = ref();
	if (!evh)
		return "";
	return Str2Cli(evh->getName());
}

void oepEventHandler::Name::set(String^ v)
{
	osgGA::EventHandler* evh = ref();
	if (!evh)
		return;
	evh->setName(Str2Std(v));
	NotifyChanged("Name");
}

bool oepEventHandler::Keep::get()
{
	return _keep;
}

void oepEventHandler::Keep::set(bool b)
{
	_keep = b;
	NotifyChanged("Keep");
}