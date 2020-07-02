#include "stdafx.h"
#include "oepUnits.h"

using namespace gEarthPack;

oepUnits::oepUnits()
{
	bind(new Units(), true);
}

void gEarthPack::oepUnits::delelehandle()
{
	del<Units>();
}

static oepUnits::oepUnits()
{
	centimeters = gcnew oepUnits();
	//centimeters->bind(&(osgEarth::Units::CENTIMETERS), false);
}

oepUnits^ oepUnits::CENTIMETERS::get()
{
	return centimeters;
}
