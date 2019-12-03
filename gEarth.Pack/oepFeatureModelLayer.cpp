#include "stdafx.h"
#include "oepFeatureModelLayer.h"

using namespace gEarthPack;

oepFeatureModelLayer::oepFeatureModelLayer(oepFeatureModelLayerOptions^ options)
{
	if (options != nullptr && options->as<osgEarth::Features::FeatureModelLayerOptions>() != NULL)
		bind(new osgEarth::Features::FeatureModelLayer(*(options->as<osgEarth::Features::FeatureModelLayerOptions>())));
	else
		bind(new osgEarth::Features::FeatureModelLayer());
}

oepFeatureModelLayer::oepFeatureModelLayer(osgEarth::Features::FeatureModelLayer* layer)
{
	bind(layer);
}