#include "stdafx.h"
#include "oepImageLayerOptions.h"
using namespace gEarthPack;

oepImageLayerOptions::oepImageLayerOptions()
{
	_handle = new osgEarth::ImageLayerOptions();
}

osgEarth::ImageLayerOptions* gEarthPack::oepImageLayerOptions::asoeImageLayerOptions()
{
	return dynamic_cast<osgEarth::ImageLayerOptions*>(_handle);
}
