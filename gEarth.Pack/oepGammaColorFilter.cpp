#include "stdafx.h"
#include "oepGammaColorFilter.h"

gEarthPack::oepGammaColorFilter::oepGammaColorFilter()
{
	_handle = new ColorFilterHandle(new osgEarth::Util::GammaColorFilter());
}

osgEarth::Util::GammaColorFilter* gEarthPack::oepGammaColorFilter::asoGammaColorFilter()
{
	return dynamic_cast<osgEarth::Util::GammaColorFilter*>(_handle->getValue());
}

void gEarthPack::oepGammaColorFilter::Reset()
{
	osgEarth::Util::GammaColorFilter* cf = asoGammaColorFilter();
	if (!cf)
		return;
	cf->setGamma(osg::Vec3f(1, 1, 1));
}

gEarthPack::oepVec3f gEarthPack::oepGammaColorFilter::Gamma::get()
{
	osgEarth::Util::GammaColorFilter* cf = asoGammaColorFilter();
	if (!cf)
		return oepVec3f();
	return oepVec3f(cf->getGamma());
}

void gEarthPack::oepGammaColorFilter::Gamma::set(oepVec3f v)
{
	osgEarth::Util::GammaColorFilter* cf = asoGammaColorFilter();
	if (!cf)
		return;
	cf->setGamma(osg::Vec3f(v.x, v.y, v.z));
	NotifyChanged("Gamma");
}

float gEarthPack::oepGammaColorFilter::V0::get()
{
	osgEarth::Util::GammaColorFilter* cf = asoGammaColorFilter();
	if (!cf)
		return 0.f;
	return cf->getGamma().x();
}

void gEarthPack::oepGammaColorFilter::V0::set(float v)
{
	osgEarth::Util::GammaColorFilter* cf = asoGammaColorFilter();
	if (!cf)
		return;
	osg::Vec3f c = cf->getGamma();
	c.x() = v;
	cf->setGamma(c);
	NotifyChanged("V0");
}

float gEarthPack::oepGammaColorFilter::V1::get()
{
	osgEarth::Util::GammaColorFilter* cf = asoGammaColorFilter();
	if (!cf)
		return 0.f;
	return cf->getGamma().y();
}

void gEarthPack::oepGammaColorFilter::V1::set(float v)
{
	osgEarth::Util::GammaColorFilter* cf = asoGammaColorFilter();
	if (!cf)
		return;
	osg::Vec3f c = cf->getGamma();
	c.y() = v;
	cf->setGamma(c);
	NotifyChanged("V1");
}

float gEarthPack::oepGammaColorFilter::V2::get()
{
	osgEarth::Util::GammaColorFilter* cf = asoGammaColorFilter();
	if (!cf)
		return 0.f;
	return cf->getGamma().z();
}

void gEarthPack::oepGammaColorFilter::V2::set(float v)
{
	osgEarth::Util::GammaColorFilter* cf = asoGammaColorFilter();
	if (!cf)
		return;
	osg::Vec3f c = cf->getGamma();
	c.z() = v;
	cf->setGamma(c);
	NotifyChanged("V2");
}
