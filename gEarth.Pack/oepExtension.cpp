#include "stdafx.h"
#include "oepExtension.h"

using namespace msclr::interop;
using namespace gEarthPack;

oepExtension::oepExtension():_handle(NULL)
{
	
}

oepExtension::~oepExtension()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

oepExtension::!oepExtension()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

osgEarth::Extension* oepExtension::asoeExtension()
{
	return _handle!=NULL ? _handle->getValue() : NULL;
}

String^ oepExtension::Name::get()
{
	osgEarth::Extension* pext = asoeExtension();
	if (!pext)
		return "";
	return marshal_as<String^>(pext->getName());
}

void oepExtension::Name::set(String^ v)
{
	osgEarth::Extension* pext = asoeExtension();
	if (!pext)
		return;
	pext->setName(marshal_as<std::string>(v));
	NotifyChanged("Name");
}
