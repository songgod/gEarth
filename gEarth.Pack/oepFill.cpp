#include "stdafx.h"
#include "oepFill.h"

using namespace gEarthPack;

oepFill::oepFill()
{
	bind(new osgEarth::Symbology::Fill(), true);
}

void gEarthPack::oepFill::delelehandle()
{
	del<osgEarth::Symbology::Fill>();
}

oepVec4f gEarthPack::oepFill::Color::get()
{
	if (!Valid)
		return oepVec4f();

	return oepVec4f(ntFill()->color());
}

void oepFill::Color::set(oepVec4f p)
{
	if (!Valid)
		return;

	ntFill()->color() = p.as();
	NotifyChanged("Color");
}
