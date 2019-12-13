#include "stdafx.h"
#include "oepExtension.h"


using namespace gEarthPack;

oepExtension::oepExtension()
{
	
}

String^ oepExtension::Name::get()
{
	osgEarth::Extension* pext = ref();
	if (!pext)
		return "";
	return Str2Cli(pext->getName());
}

void oepExtension::Name::set(String^ v)
{
	osgEarth::Extension* pext = ref();
	if (!pext)
		return;
	pext->setName(Str2Std(v));
	NotifyChanged("Name");
}
