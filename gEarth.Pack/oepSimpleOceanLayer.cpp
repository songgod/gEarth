#include "stdafx.h"
#include "oepSimpleOceanLayer.h"

using namespace gEarthPack;

oepSimpleOceanLayer::oepSimpleOceanLayer(oepSimpleOceanLayerOptions^ options)
{
	if (options != nullptr && options->as<osgEarth::Util::SimpleOceanLayerOptions>() != NULL)
		_handle->setValue(new osgEarth::Util::SimpleOceanLayer(*(options->as<osgEarth::Util::SimpleOceanLayerOptions>())));
	else
		_handle->setValue(new osgEarth::Util::SimpleOceanLayer());
}

oepSimpleOceanLayer::oepSimpleOceanLayer(osgEarth::Util::SimpleOceanLayer* layer)
{
	_handle->setValue(layer);
}

float oepSimpleOceanLayer::MaxAltitude::get()
{
	osgEarth::Util::SimpleOceanLayer* ol = as<osgEarth::Util::SimpleOceanLayer>();
	if (!ol)
		return 0.0;
	return ol->getMaxAltitude();
}

void oepSimpleOceanLayer::MaxAltitude::set(float v)
{
	osgEarth::Util::SimpleOceanLayer* ol = as<osgEarth::Util::SimpleOceanLayer>();
	if (!ol)
		return;
	ol->setMaxAltitude(v);
	NotifyChanged("MaxAltitude");
}

oepVec4f oepSimpleOceanLayer::Color::get()
{
	osgEarth::Util::SimpleOceanLayer* ol = as<osgEarth::Util::SimpleOceanLayer>();
	if (!ol)
		return oepVec4f();

	osgEarth::Color c = ol->getColor();
	return oepVec4f(c.x(), c.y(), c.z(), c.a());
}

void oepSimpleOceanLayer::Color::set(oepVec4f v)
{
	osgEarth::Util::SimpleOceanLayer* ol = as<osgEarth::Util::SimpleOceanLayer>();
	if (!ol)
		return;
	ol->setColor(osgEarth::Color(v.x,v.y,v.z,v.a));
	NotifyChanged("Color");
}

float oepSimpleOceanLayer::SeaLevel::get()
{
	osgEarth::Util::SimpleOceanLayer* ol = as<osgEarth::Util::SimpleOceanLayer>();
	if (!ol)
		return 0.0;
	return ol->getSeaLevel();
}

void oepSimpleOceanLayer::SeaLevel::set(float v)
{
	osgEarth::Util::SimpleOceanLayer* ol = as<osgEarth::Util::SimpleOceanLayer>();
	if (!ol)
		return;
	ol->setSeaLevel(v);
	NotifyChanged("SeaLevel");
}
