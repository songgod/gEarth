#include "stdafx.h"
#include "oepElevationLayer.h"

using namespace gEarthPack;

oepElevationLayer::oepElevationLayer(oepElevationLayerOptions^ elevationlayeroptions)
{
	if (elevationlayeroptions != nullptr && elevationlayeroptions->as<osgEarth::ElevationLayerOptions>() != NULL)
		bind(new osgEarth::ElevationLayer(*(elevationlayeroptions->as<osgEarth::ElevationLayerOptions>())));
	else
		bind(new osgEarth::ElevationLayer());
}

oepElevationLayer::oepElevationLayer(osgEarth::ElevationLayer* pElevationLayer)
{
	bind(pElevationLayer);
}



