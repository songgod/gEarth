#include "stdafx.h"
#include "oepModelLayer.h"

using namespace gEarthPack;

oepModelLayer::oepModelLayer(oepModelLayerOptions^ options)
{
	if (options != nullptr && options->as<osgEarth::ModelLayerOptions>() != NULL)
		bind(new osgEarth::ModelLayer(*(options->as<osgEarth::ModelLayerOptions>())));
	else
		bind(new osgEarth::ModelLayer());
}
oepModelLayer::oepModelLayer(osgEarth::ModelLayer* layer)
{
	bind(layer);
}
