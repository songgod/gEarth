#include "stdafx.h"
#include "oepUnits.h"

using namespace gEarthPack;

oepUnits::oepUnits()
{
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
