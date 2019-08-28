#include "stdafx.h"
#include "oepElevationLayer.h"

using namespace gEarthPack;

oepElevationLayer::oepElevationLayer(oepElevationLayerOptions^ elevationlayeroptions)
{
	if (elevationlayeroptions != nullptr && elevationlayeroptions->asoeElevationLayerOptions() != NULL)
		_handle->setValue(new osgEarth::ElevationLayer(*(elevationlayeroptions->asoeElevationLayerOptions())));
	else
		_handle->setValue(new osgEarth::ElevationLayer());
}

oepElevationLayer::oepElevationLayer(osgEarth::ElevationLayer* pElevationLayer)
{
	_handle->setValue(pElevationLayer);
}

osgEarth::ElevationLayer * oepElevationLayer::asoeElevationLayer()
{
	return dynamic_cast<osgEarth::ElevationLayer*>(_handle->getValue());
}



