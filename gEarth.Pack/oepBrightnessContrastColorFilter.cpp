#include "stdafx.h"
#include "oepBrightnessContrastColorFilter.h"

using namespace gEarthPack;
using namespace osgEarth::Util;

oepBrightnessContrastColorFilter::oepBrightnessContrastColorFilter()
{
	_handle->setValue(new BrightnessContrastColorFilter());
}

void oepBrightnessContrastColorFilter::Reset()
{
	BrightnessContrastColorFilter* cf = as<BrightnessContrastColorFilter>();
	if (!cf)
		return;
	cf->setBrightnessContrast(osg::Vec2f(1, 1));
}

oepVec2f oepBrightnessContrastColorFilter::BrightnessContrast::get()
{
	BrightnessContrastColorFilter* cf = as<BrightnessContrastColorFilter>();
	if (!cf)
		return oepVec2f();
	return oepVec2f(cf->getBrightnessContrast());
}

void oepBrightnessContrastColorFilter::BrightnessContrast::set(oepVec2f v)
{
	BrightnessContrastColorFilter* cf = as<BrightnessContrastColorFilter>();
	if (!cf)
		return;
	cf->setBrightnessContrast(osg::Vec2f(v.x, v.y));
	NotifyChanged("BrightnessContrast");
}

float oepBrightnessContrastColorFilter::V0::get()
{
	BrightnessContrastColorFilter* cf = as<BrightnessContrastColorFilter>();
	if (!cf)
		return 0.f;
	return cf->getBrightnessContrast().x();
}

void oepBrightnessContrastColorFilter::V0::set(float v)
{
	BrightnessContrastColorFilter* cf = as<BrightnessContrastColorFilter>();
	if (!cf)
		return;
	osg::Vec2f c = cf->getBrightnessContrast();
	c.x() = v;
	cf->setBrightnessContrast(c);
	NotifyChanged("V0");
}

float oepBrightnessContrastColorFilter::V1::get()
{
	BrightnessContrastColorFilter* cf = as<BrightnessContrastColorFilter>();
	if (!cf)
		return 0.f;
	return cf->getBrightnessContrast().y();
}

void oepBrightnessContrastColorFilter::V1::set(float v)
{
	BrightnessContrastColorFilter* cf = as<BrightnessContrastColorFilter>();
	if (!cf)
		return;
	osg::Vec2f c = cf->getBrightnessContrast();
	c.y() = v;
	cf->setBrightnessContrast(c);
	NotifyChanged("V1");
}