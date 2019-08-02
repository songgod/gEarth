#include "stdafx.h"
#include "oepBrightnessContrastColorFilter.h"

using namespace gEarthPack;

oepBrightnessContrastColorFilter::oepBrightnessContrastColorFilter()
{
	_handle = new ColorFilterHandle(new osgEarth::Util::BrightnessContrastColorFilter());
}

osgEarth::Util::BrightnessContrastColorFilter* oepBrightnessContrastColorFilter::asoeBrightnessContrastColorFilter()
{
	return dynamic_cast<osgEarth::Util::BrightnessContrastColorFilter*>(_handle->getValue());
}

void oepBrightnessContrastColorFilter::Reset()
{
	osgEarth::Util::BrightnessContrastColorFilter* cf = asoeBrightnessContrastColorFilter();
	if (!cf)
		return;
	cf->setBrightnessContrast(osg::Vec2f(1, 1));
}

oepVec2f oepBrightnessContrastColorFilter::BrightnessContrast::get()
{
	osgEarth::Util::BrightnessContrastColorFilter* cf = asoeBrightnessContrastColorFilter();
	if (!cf)
		return oepVec2f();
	return oepVec2f(cf->getBrightnessContrast());
}

void oepBrightnessContrastColorFilter::BrightnessContrast::set(oepVec2f v)
{
	osgEarth::Util::BrightnessContrastColorFilter* cf = asoeBrightnessContrastColorFilter();
	if (!cf)
		return;
	cf->setBrightnessContrast(osg::Vec2f(v.x, v.y));
	NotifyChanged("BrightnessContrast");
}

float oepBrightnessContrastColorFilter::V0::get()
{
	osgEarth::Util::BrightnessContrastColorFilter* cf = asoeBrightnessContrastColorFilter();
	if (!cf)
		return 0.f;
	return cf->getBrightnessContrast().x();
}

void oepBrightnessContrastColorFilter::V0::set(float v)
{
	osgEarth::Util::BrightnessContrastColorFilter* cf = asoeBrightnessContrastColorFilter();
	if (!cf)
		return;
	osg::Vec2f c = cf->getBrightnessContrast();
	c.x() = v;
	cf->setBrightnessContrast(c);
	NotifyChanged("V0");
}

float oepBrightnessContrastColorFilter::V1::get()
{
	osgEarth::Util::BrightnessContrastColorFilter* cf = asoeBrightnessContrastColorFilter();
	if (!cf)
		return 0.f;
	return cf->getBrightnessContrast().y();
}

void oepBrightnessContrastColorFilter::V1::set(float v)
{
	osgEarth::Util::BrightnessContrastColorFilter* cf = asoeBrightnessContrastColorFilter();
	if (!cf)
		return;
	osg::Vec2f c = cf->getBrightnessContrast();
	c.y() = v;
	cf->setBrightnessContrast(c);
	NotifyChanged("V1");
}