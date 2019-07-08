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

float gEarthPack::oepSimpleOceanLayer::MaxAltitude::get()
{
	osgEarth::Util::SimpleOceanLayer* ol = asoeSimpleOceanLayer();
	if (!ol)
		return 0.0;
	return ol->getMaxAltitude();
}

void gEarthPack::oepSimpleOceanLayer::MaxAltitude::set(float v)
{
	osgEarth::Util::SimpleOceanLayer* ol = asoeSimpleOceanLayer();
	if (!ol)
		return;
	ol->setMaxAltitude(v);
	NotifyChanged("MaxAltitude");
}

gEarthPack::oepVec4f gEarthPack::oepSimpleOceanLayer::Color::get()
{
	osgEarth::Util::SimpleOceanLayer* ol = asoeSimpleOceanLayer();
	if (!ol)
		return oepVec4f();

	osgEarth::Color c = ol->getColor();
	return oepVec4f(c.x(), c.y(), c.z(), c.a());
}

void gEarthPack::oepSimpleOceanLayer::Color::set(oepVec4f v)
{
	osgEarth::Util::SimpleOceanLayer* ol = asoeSimpleOceanLayer();
	if (!ol)
		return;
	ol->setColor(osgEarth::Color(v.x,v.y,v.z,v.a));
	NotifyChanged("Color");
}
