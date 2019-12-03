#include "stdafx.h"
#include "oepHSLColorFilter.h"

using namespace gEarthPack;

oepHSLColorFilter::oepHSLColorFilter()
{
	bind(new osgEarth::Util::HSLColorFilter());
}

void oepHSLColorFilter::Reset()
{
	osgEarth::Util::HSLColorFilter* cf = as<osgEarth::Util::HSLColorFilter>();
	if (!cf)
		return;
	cf->setHSLOffset(osg::Vec3f(0, 0, 0));
}

oepVec3f oepHSLColorFilter::Offset::get()
{
	osgEarth::Util::HSLColorFilter* cf = as<osgEarth::Util::HSLColorFilter>();
	if (!cf)
		return oepVec3f();
	return oepVec3f(cf->getHSLOffset());
}

void oepHSLColorFilter::Offset::set(oepVec3f v)
{
	osgEarth::Util::HSLColorFilter* cf = as<osgEarth::Util::HSLColorFilter>();
	if (!cf)
		return;
	cf->setHSLOffset(osg::Vec3f(v.x, v.y, v.z));
	NotifyChanged("Offset");
}


float oepHSLColorFilter::H::get()
{
	osgEarth::Util::HSLColorFilter* cf = as<osgEarth::Util::HSLColorFilter>();
	if (!cf)
		return 0.f;
	return cf->getHSLOffset().x();
}

void oepHSLColorFilter::H::set(float v)
{
	osgEarth::Util::HSLColorFilter* cf = as<osgEarth::Util::HSLColorFilter>();
	if (!cf)
		return;
	osg::Vec3f c = cf->getHSLOffset();
	c.x() = v;
	cf->setHSLOffset(c);
	NotifyChanged("H");
}

float oepHSLColorFilter::S::get()
{
	osgEarth::Util::HSLColorFilter* cf = as<osgEarth::Util::HSLColorFilter>();
	if (!cf)
		return 0.f;
	return cf->getHSLOffset().y();
}

void oepHSLColorFilter::S::set(float v)
{
	osgEarth::Util::HSLColorFilter* cf = as<osgEarth::Util::HSLColorFilter>();
	if (!cf)
		return;
	osg::Vec3f c = cf->getHSLOffset();
	c.y() = v;
	cf->setHSLOffset(c);
	NotifyChanged("S");
}

float oepHSLColorFilter::L::get()
{
	osgEarth::Util::HSLColorFilter* cf = as<osgEarth::Util::HSLColorFilter>();
	if (!cf)
		return 0.f;
	return cf->getHSLOffset().z();
}

void oepHSLColorFilter::L::set(float v)
{
	osgEarth::Util::HSLColorFilter* cf = as<osgEarth::Util::HSLColorFilter>();
	if (!cf)
		return;
	osg::Vec3f c = cf->getHSLOffset();
	c.z() = v;
	cf->setHSLOffset(c);
	NotifyChanged("L");
}
