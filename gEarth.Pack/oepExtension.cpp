#include "stdafx.h"
#include "oepExtension.h"

using namespace msclr::interop;
using namespace gEarthPack;

oepExtension::oepExtension()
{
	
}

String^ oepExtension::Name::get()
{
	osgEarth::Extension* pext = ref();
	if (!pext)
		return "";
	return marshal_as<String^>(pext->getName());
}

void oepExtension::Name::set(String^ v)
{
	osgEarth::Extension* pext = ref();
	if (!pext)
		return;
	pext->setName(marshal_as<std::string>(v));
	NotifyChanged("Name");
}
