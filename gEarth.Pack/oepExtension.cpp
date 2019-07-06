#include "stdafx.h"
#include "oepExtension.h"
#include <msclr\marshal_cppstd.h>  

using namespace msclr::interop;

gEarthPack::oepExtension::oepExtension():_handle(NULL)
{
	
}

gEarthPack::oepExtension::~oepExtension()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

gEarthPack::oepExtension::!oepExtension()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

osgEarth::Extension* gEarthPack::oepExtension::asoeExtension()
{
	return _handle!=NULL ? _handle->getValue() : NULL;
}

String^ gEarthPack::oepExtension::Name::get()
{
	osgEarth::Extension* pext = asoeExtension();
	if (!pext)
		return "";
	return marshal_as<String^>(pext->getName());
}

void gEarthPack::oepExtension::Name::set(String^ v)
{
	osgEarth::Extension* pext = asoeExtension();
	if (!pext)
		return;
	pext->setName(marshal_as<std::string>(v));
	NotifyChanged("Name");
}
