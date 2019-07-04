#include "stdafx.h"
#include "oepHSLColorFilter.h"


gEarthPack::oepHSLColorFilter::oepHSLColorFilter()
{
	_handle = new ColorFilterHandle(new osgEarth::Util::HSLColorFilter());
}

osgEarth::Util::HSLColorFilter* gEarthPack::oepHSLColorFilter::asoeHSLColorFilter()
{
	return dynamic_cast<osgEarth::Util::HSLColorFilter*>(_handle->getValue());
}

void gEarthPack::oepHSLColorFilter::Reset()
{
	osgEarth::Util::HSLColorFilter* cf = asoeHSLColorFilter();
	if (!cf)
		return;
	cf->setHSLOffset(osg::Vec3f(0, 0, 0));
}

gEarthPack::oepVec3f gEarthPack::oepHSLColorFilter::Offset::get()
{
	osgEarth::Util::HSLColorFilter* cf = asoeHSLColorFilter();
	if (!cf)
		return oepVec3f();
	return oepVec3f(cf->getHSLOffset());
}

void gEarthPack::oepHSLColorFilter::Offset::set(oepVec3f v)
{
	osgEarth::Util::HSLColorFilter* cf = asoeHSLColorFilter();
	if (!cf)
		return;
	cf->setHSLOffset(osg::Vec3f(v.x, v.y, v.z));
	NotifyChanged("Offset");
}


float gEarthPack::oepHSLColorFilter::H::get()
{
	osgEarth::Util::HSLColorFilter* cf = asoeHSLColorFilter();
	if (!cf)
		return 0.f;
	return cf->getHSLOffset().x();
}

void gEarthPack::oepHSLColorFilter::H::set(float v)
{
	osgEarth::Util::HSLColorFilter* cf = asoeHSLColorFilter();
	if (!cf)
		return;
	osg::Vec3f c = cf->getHSLOffset();
	c.x() = v;
	cf->setHSLOffset(c);
	NotifyChanged("H");
}

float gEarthPack::oepHSLColorFilter::S::get()
{
	osgEarth::Util::HSLColorFilter* cf = asoeHSLColorFilter();
	if (!cf)
		return 0.f;
	return cf->getHSLOffset().y();
}

void gEarthPack::oepHSLColorFilter::S::set(float v)
{
	osgEarth::Util::HSLColorFilter* cf = asoeHSLColorFilter();
	if (!cf)
		return;
	osg::Vec3f c = cf->getHSLOffset();
	c.y() = v;
	cf->setHSLOffset(c);
	NotifyChanged("S");
}

float gEarthPack::oepHSLColorFilter::L::get()
{
	osgEarth::Util::HSLColorFilter* cf = asoeHSLColorFilter();
	if (!cf)
		return 0.f;
	return cf->getHSLOffset().z();
}

void gEarthPack::oepHSLColorFilter::L::set(float v)
{
	osgEarth::Util::HSLColorFilter* cf = asoeHSLColorFilter();
	if (!cf)
		return;
	osg::Vec3f c = cf->getHSLOffset();
	c.z() = v;
	cf->setHSLOffset(c);
	NotifyChanged("L");
}
