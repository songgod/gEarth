#include "stdafx.h"
#include "oepImageLayerOptions.h"

using namespace gEarthPack;

oepImageLayerOptions::oepImageLayerOptions()
{
	_handle = new osgEarth::ImageLayerOptions();
}

osgEarth::ImageLayerOptions* oepImageLayerOptions::asoeImageLayerOptions()
{
	return dynamic_cast<osgEarth::ImageLayerOptions*>(_handle);
}
