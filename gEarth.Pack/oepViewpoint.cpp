#include "stdafx.h"
#include "oepViewpoint.h"

using namespace msclr::interop;
using namespace gEarthPack;

oepViewpoint::oepViewpoint()
{
	setVal(new osgEarth::Viewpoint());
}

oepViewpoint::oepViewpoint(osgEarth::Viewpoint& vp)
{
	setVal(new osgEarth::Viewpoint());
	setVal(vp);
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
