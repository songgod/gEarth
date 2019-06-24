#include "stdafx.h"
#include "oepSimpleSkyOptions.h"
#include <osgEarthDrivers/sky_simple/SimpleSkyOptions>

gEarthPack::oepSimpleSkyOptions::oepSimpleSkyOptions()
{
	_handle = new osgEarth::SimpleSky::SimpleSkyOptions();
}
