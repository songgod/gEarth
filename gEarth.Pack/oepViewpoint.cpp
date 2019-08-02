#include "stdafx.h"
#include "oepViewpoint.h"
#include <msclr\marshal_cppstd.h>  

using namespace msclr::interop;
using namespace gEarthPack;

oepViewpoint::oepViewpoint() : _handle(new osgEarth::Viewpoint()), _ownhandle(true)
{
}


oepViewpoint::~oepViewpoint()
{
	if (_handle != NULL && _ownhandle)
	{
		delete _handle;
		_handle = NULL;
	}
}

oepViewpoint::!oepViewpoint()
{
	if (_handle != NULL && _ownhandle)
	{
		delete _handle;
		_handle = NULL;
	}
}

String^ oepViewpoint::Name::get()
{
	if (!_handle)
		return "";
	return marshal_as<String^>(_handle->name().value());
}

void oepViewpoint::Name::set(String^ v)
{
	if (!_handle)
		return;
	_handle->name() = marshal_as<std::string>(v);
	NotifyChanged("Name");
}

bool oepViewpoint::IsValid::get()
{
	if (!_handle)
		return false;
	return _handle->isValid();
}

oepViewpoint::oepViewpoint(const osgEarth::Viewpoint& vp): _handle(new osgEarth::Viewpoint()), _ownhandle(true)
{
	(*_handle) = vp;
}

void oepViewpoint::setHandle(osgEarth::Viewpoint* handle)
{
	if (_handle != NULL && _ownhandle)
	{
		delete _handle;
		_handle = NULL;
	}
	_handle = handle;
	_ownhandle = false;
}

void oepViewpoint::resetHandle()
{
	if (_ownhandle)
		return;
	_handle = new osgEarth::Viewpoint();
	_ownhandle = true;
}

osgEarth::Viewpoint* oepViewpoint::asoeViewpoint()
{
	return _handle;
}
