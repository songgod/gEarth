#include "stdafx.h"
#include "oepViewpoint.h"
#include <msclr\marshal_cppstd.h>  

using namespace msclr::interop;


gEarthPack::oepViewpoint::oepViewpoint() : _handle(new osgEarth::Viewpoint()), _ownhandle(true)
{
}


gEarthPack::oepViewpoint::~oepViewpoint()
{
	if (_handle != NULL && _ownhandle)
	{
		delete _handle;
		_handle = NULL;
	}
}

gEarthPack::oepViewpoint::!oepViewpoint()
{
	if (_handle != NULL && _ownhandle)
	{
		delete _handle;
		_handle = NULL;
	}
}

String^ gEarthPack::oepViewpoint::Name::get()
{
	if (!_handle)
		return "";
	return marshal_as<String^>(_handle->name().value());
}

void gEarthPack::oepViewpoint::Name::set(String^ v)
{
	if (!_handle)
		return;
	_handle->name() = marshal_as<std::string>(v);
	NotifyChanged("Name");
}

bool gEarthPack::oepViewpoint::IsValid::get()
{
	if (!_handle)
		return false;
	return _handle->isValid();
}

gEarthPack::oepViewpoint::oepViewpoint(const osgEarth::Viewpoint& vp): _handle(new osgEarth::Viewpoint()), _ownhandle(true)
{
	(*_handle) = vp;
}

void gEarthPack::oepViewpoint::setHandle(osgEarth::Viewpoint* handle)
{
	if (_handle != NULL && _ownhandle)
	{
		delete _handle;
		_handle = NULL;
	}
	_handle = handle;
	_ownhandle = false;
}

void gEarthPack::oepViewpoint::resetHandle()
{
	if (_ownhandle)
		return;
	_handle = new osgEarth::Viewpoint();
	_ownhandle = true;
}

osgEarth::Viewpoint* gEarthPack::oepViewpoint::asoeViewpoint()
{
	return _handle;
}
