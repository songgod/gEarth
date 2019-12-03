#include "stdafx.h"
#include "oepImageLayerOptions.h"

using namespace gEarthPack;

oepImageLayerOptions::oepImageLayerOptions()
{
	bind(new osgEarth::ImageLayerOptions(),true);
}
