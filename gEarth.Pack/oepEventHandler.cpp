#include "stdafx.h"
#include "oepEventHandler.h"
#include <msclr\marshal_cppstd.h>  

using namespace msclr::interop;

gEarthPack::oepEventHandler::oepEventHandler()
{
	_handle = new EventHandlerHandle();
}

gEarthPack::oepEventHandler::~oepEventHandler()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

gEarthPack::oepEventHandler::!oepEventHandler()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

osgGA::EventHandler* gEarthPack::oepEventHandler::asosgEventHandler()
{
	return _handle != NULL ? _handle->getValue() : NULL;
}

String^ gEarthPack::oepEventHandler::Name::get()
{
	osgGA::EventHandler* evh = asosgEventHandler();
	if (!evh)
		return "";
	return marshal_as<String^>(evh->getName());
}

void gEarthPack::oepEventHandler::Name::set(String^ v)
{
	osgGA::EventHandler* evh = asosgEventHandler();
	if (!evh)
		return;
	evh->setName(marshal_as<std::string>(v));
	NotifyChanged("Name");
}