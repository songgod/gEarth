#include "stdafx.h"
#include "oepElevationLayer.h"

using namespace gEarthPack;

oepElevationLayer::oepElevationLayer(oepElevationLayerOptions^ elevationlayeroptions)
{
	if (elevationlayeroptions != nullptr && elevationlayeroptions->as<osgEarth::ElevationLayerOptions>() != NULL)
		setRef(new osgEarth::ElevationLayer(*(elevationlayeroptions->as<osgEarth::ElevationLayerOptions>())));
	else
		setRef(new osgEarth::ElevationLayer());
}

oepElevationLayer::oepElevationLayer(osgEarth::ElevationLayer* pElevationLayer)
{
	setRef(pElevationLayer);
}



