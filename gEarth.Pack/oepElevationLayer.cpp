#include "stdafx.h"
#include "oepElevationLayer.h"

using namespace gEarthPack;

oepElevationLayer::oepElevationLayer(oepElevationLayerOptions^ elevationlayeroptions)
{
	if (elevationlayeroptions != nullptr && elevationlayeroptions->as<osgEarth::ElevationLayerOptions>() != NULL)
		_handle->setValue(new osgEarth::ElevationLayer(*(elevationlayeroptions->as<osgEarth::ElevationLayerOptions>())));
	else
		_handle->setValue(new osgEarth::ElevationLayer());
}

oepElevationLayer::oepElevationLayer(osgEarth::ElevationLayer* pElevationLayer)
{
	_handle->setValue(pElevationLayer);
}



