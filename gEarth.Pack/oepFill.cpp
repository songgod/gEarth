#include "stdafx.h"
#include "oepFill.h"

using namespace gEarthPack;

oepFill::oepFill()
{
	bind(new osgEarth::Symbology::Fill(), true);
}

oepVec4f gEarthPack::oepFill::Color::get()
{
	if (!Valid)
		return oepVec4f();

	return oepVec4f(val()->color());
}

void oepFill::Color::set(oepVec4f p)
{
	if (!Valid)
		return;

	val()->color() = p.as();
	NotifyChanged("Color");
}
