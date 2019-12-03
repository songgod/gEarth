#include "stdafx.h"
#include "oepGammaColorFilter.h"

using namespace gEarthPack;

oepGammaColorFilter::oepGammaColorFilter()
{
	bind(new osgEarth::Util::GammaColorFilter());
}

void oepGammaColorFilter::Reset()
{
	osgEarth::Util::GammaColorFilter* cf = as<osgEarth::Util::GammaColorFilter>();
	if (!cf)
		return;
	cf->setGamma(osg::Vec3f(1, 1, 1));
}

oepVec3f oepGammaColorFilter::Gamma::get()
{
	osgEarth::Util::GammaColorFilter* cf = as<osgEarth::Util::GammaColorFilter>();
	if (!cf)
		return oepVec3f();
	return oepVec3f(cf->getGamma());
}

void oepGammaColorFilter::Gamma::set(oepVec3f v)
{
	osgEarth::Util::GammaColorFilter* cf = as<osgEarth::Util::GammaColorFilter>();
	if (!cf)
		return;
	cf->setGamma(osg::Vec3f(v.x, v.y, v.z));
	NotifyChanged("Gamma");
}

float oepGammaColorFilter::V0::get()
{
	osgEarth::Util::GammaColorFilter* cf = as<osgEarth::Util::GammaColorFilter>();
	if (!cf)
		return 0.f;
	return cf->getGamma().x();
}

void oepGammaColorFilter::V0::set(float v)
{
	osgEarth::Util::GammaColorFilter* cf = as<osgEarth::Util::GammaColorFilter>();
	if (!cf)
		return;
	osg::Vec3f c = cf->getGamma();
	c.x() = v;
	cf->setGamma(c);
	NotifyChanged("V0");
}

float oepGammaColorFilter::V1::get()
{
	osgEarth::Util::GammaColorFilter* cf = as<osgEarth::Util::GammaColorFilter>();
	if (!cf)
		return 0.f;
	return cf->getGamma().y();
}

void oepGammaColorFilter::V1::set(float v)
{
	osgEarth::Util::GammaColorFilter* cf = as<osgEarth::Util::GammaColorFilter>();
	if (!cf)
		return;
	osg::Vec3f c = cf->getGamma();
	c.y() = v;
	cf->setGamma(c);
	NotifyChanged("V1");
}

float oepGammaColorFilter::V2::get()
{
	osgEarth::Util::GammaColorFilter* cf = as<osgEarth::Util::GammaColorFilter>();
	if (!cf)
		return 0.f;
	return cf->getGamma().z();
}

void oepGammaColorFilter::V2::set(float v)
{
	osgEarth::Util::GammaColorFilter* cf = as<osgEarth::Util::GammaColorFilter>();
	if (!cf)
		return;
	osg::Vec3f c = cf->getGamma();
	c.z() = v;
	cf->setGamma(c);
	NotifyChanged("V2");
}
