#include "stdafx.h"
#include "oepViewpoint.h"


using namespace gEarthPack;

oepViewpoint::oepViewpoint()
{
	bind(new osgEarth::Viewpoint(),true);
}

oepViewpoint::oepViewpoint(osgEarth::Viewpoint& vp)
{
	bind(new osgEarth::Viewpoint(vp),true);
}

void oepViewpoint::delelehandle()
{
	del<osgEarth::Viewpoint>();
}

String^ oepViewpoint::Name::get()
{
	if (!Valid)
		return "";
	return Str2Cli(as<osgEarth::Viewpoint>()->name().value());
}

void oepViewpoint::Name::set(String^ v)
{
	if (!Valid)
		return;
	as<osgEarth::Viewpoint>()->name() = Str2Std(v);
	NotifyChanged("Name");
}

bool oepViewpoint::IsValid::get()
{
	if (!Valid)
		return false;
	return as<osgEarth::Viewpoint>()->isValid();
}
