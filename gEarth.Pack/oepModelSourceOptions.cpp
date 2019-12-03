#include "stdafx.h"
#include "oepModelSourceOptions.h"

using namespace gEarthPack;

oepModelSourceOptions::oepModelSourceOptions()
{
	bind(new osgEarth::ModelSourceOptions(),true);
}
