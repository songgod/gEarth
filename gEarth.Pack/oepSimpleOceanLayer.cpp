#include "stdafx.h"
#include "oepSimpleOceanLayer.h"

using namespace gEarthPack;

oepSimpleOceanLayer::oepSimpleOceanLayer(oepSimpleOceanLayerOptions^ options)
{
	if (options != nullptr && options->asoeSimpleOceanLayerOptions() != NULL)
		_handle->setValue(new osgEarth::Util::SimpleOceanLayer(*(options->asoeSimpleOceanLayerOptions())));
	else
		_handle->setValue(new osgEarth::Util::SimpleOceanLayer());
}

osgEarth::Util::SimpleOceanLayer* gEarthPack::oepSimpleOceanLayer::asoeSimpleOceanLayer()
{
	return dynamic_cast<osgEarth::Util::SimpleOceanLayer*>(_handle->getValue());
}

gEarthPack::oepSimpleOceanLayer::oepSimpleOceanLayer(osgEarth::Util::SimpleOceanLayer* layer)
{
	_handle->setValue(layer);
}