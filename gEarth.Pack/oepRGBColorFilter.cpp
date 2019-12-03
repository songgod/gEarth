#include "stdafx.h"
#include "oepRGBColorFilter.h"

using namespace gEarthPack;

oepRGBColorFilter::oepRGBColorFilter()
{
	bind(new osgEarth::Util::RGBColorFilter());
}

void oepRGBColorFilter::Reset()
{
	osgEarth::Util::RGBColorFilter* cf = as<osgEarth::Util::RGBColorFilter>();
	if (!cf)
		return;
	cf->setRGBOffset(osg::Vec3f(0,0,0));
}

oepVec3f oepRGBColorFilter::Offset::get()
{
	osgEarth::Util::RGBColorFilter* cf = as<osgEarth::Util::RGBColorFilter>();
	if (!cf)
		return oepVec3f();
	return oepVec3f(cf->getRGBOffset());
}

void oepRGBColorFilter::Offset::set(oepVec3f v)
{
	osgEarth::Util::RGBColorFilter* cf = as<osgEarth::Util::RGBColorFilter>();
	if (!cf)
		return;
	cf->setRGBOffset(osg::Vec3f(v.x, v.y, v.z));
	NotifyChanged("Offset");
}

float oepRGBColorFilter::R::get()
{
	osgEarth::Util::RGBColorFilter* cf = as<osgEarth::Util::RGBColorFilter>();
	if (!cf)
		return 0.f;
	return cf->getRGBOffset().x();
}

void oepRGBColorFilter::R::set(float v)
{
	osgEarth::Util::RGBColorFilter* cf = as<osgEarth::Util::RGBColorFilter>();
	if (!cf)
		return;
	osg::Vec3f c = cf->getRGBOffset();
	c.x() = v;
	cf->setRGBOffset(c);
	NotifyChanged("R");
}

float oepRGBColorFilter::G::get()
{
	osgEarth::Util::RGBColorFilter* cf = as<osgEarth::Util::RGBColorFilter>();
	if (!cf)
		return 0.f;
	return cf->getRGBOffset().y();
}

void oepRGBColorFilter::G::set(float v)
{
	osgEarth::Util::RGBColorFilter* cf = as<osgEarth::Util::RGBColorFilter>();
	if (!cf)
		return;
	osg::Vec3f c = cf->getRGBOffset();
	c.y() = v;
	cf->setRGBOffset(c);
	NotifyChanged("G");
}

float oepRGBColorFilter::B::get()
{
	osgEarth::Util::RGBColorFilter* cf = as<osgEarth::Util::RGBColorFilter>();
	if (!cf)
		return 0.f;
	return cf->getRGBOffset().z();
}

void oepRGBColorFilter::B::set(float v)
{
	osgEarth::Util::RGBColorFilter* cf = as<osgEarth::Util::RGBColorFilter>();
	if (!cf)
		return;
	osg::Vec3f c = cf->getRGBOffset();
	c.z() = v;
	cf->setRGBOffset(c);
	NotifyChanged("B");
}
