#include "stdafx.h"
#include "oepConfigOptions.h"


using namespace gEarthPack;

oepConfigOptions::oepConfigOptions()
{
}

void gEarthPack::oepConfigOptions::delelehandle()
{
	del<osgEarth::ConfigOptions>();
}
