#include "stdafx.h"
#include "oepEventHandler.h"

using namespace msclr::interop;
using namespace gEarthPack;

oepEventHandler::oepEventHandler()
{
	_handle = new EventHandlerHandle();
}

oepEventHandler::~oepEventHandler()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

oepEventHandler::!oepEventHandler()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

osgGA::EventHandler* oepEventHandler::asosgEventHandler()
{
	return _handle != NULL ? _handle->getValue() : NULL;
}

String^ oepEventHandler::Name::get()
{
	osgGA::EventHandler* evh = asosgEventHandler();
	if (!evh)
		return "";
	return marshal_as<String^>(evh->getName());
}

void oepEventHandler::Name::set(String^ v)
{
	osgGA::EventHandler* evh = asosgEventHandler();
	if (!evh)
		return;
	evh->setName(marshal_as<std::string>(v));
	NotifyChanged("Name");
}