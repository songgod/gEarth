#include "stdafx.h"
#include "oepEventHandler.h"

using namespace msclr::interop;
using namespace gEarthPack;

oepEventHandler::oepEventHandler()
{
	
}

String^ oepEventHandler::Name::get()
{
	osgGA::EventHandler* evh = ref();
	if (!evh)
		return "";
	return marshal_as<String^>(evh->getName());
}

void oepEventHandler::Name::set(String^ v)
{
	osgGA::EventHandler* evh = ref();
	if (!evh)
		return;
	evh->setName(marshal_as<std::string>(v));
	NotifyChanged("Name");
}