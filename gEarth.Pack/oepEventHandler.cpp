#include "stdafx.h"
#include "oepEventHandler.h"


using namespace gEarthPack;

oepEventHandler::oepEventHandler()
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