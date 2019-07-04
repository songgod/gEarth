#include "stdafx.h"
#include "oepRGBColorFilter.h"


gEarthPack::oepRGBColorFilter::oepRGBColorFilter()
{
	_handle = new ColorFilterHandle(new osgEarth::Util::RGBColorFilter());
}

void gEarthPack::oepRGBColorFilter::Reset()
{
	osgEarth::Util::RGBColorFilter* cf = asoeRGBColorFilter();
	if (!cf)
		return;
	cf->setRGBOffset(osg::Vec3f(0,0,0));
}

osgEarth::Util::RGBColorFilter* gEarthPack::oepRGBColorFilter::asoeRGBColorFilter()
{
	return dynamic_cast<osgEarth::Util::RGBColorFilter*>(_handle->getValue());
}

gEarthPack::oepVec3f gEarthPack::oepRGBColorFilter::Offset::get()
{
	osgEarth::Util::RGBColorFilter* cf = asoeRGBColorFilter();
	if (!cf)
		return oepVec3f();
	return oepVec3f(cf->getRGBOffset());
}

void gEarthPack::oepRGBColorFilter::Offset::set(oepVec3f v)
{
	osgEarth::Util::RGBColorFilter* cf = asoeRGBColorFilter();
	if (!cf)
		return;
	cf->setRGBOffset(osg::Vec3f(v.x, v.y, v.z));
	NotifyChanged("Offset");
}

float gEarthPack::oepRGBColorFilter::R::get()
{
	osgEarth::Util::RGBColorFilter* cf = asoeRGBColorFilter();
	if (!cf)
		return 0.f;
	return cf->getRGBOffset().x();
}

void gEarthPack::oepRGBColorFilter::R::set(float v)
{
	osgEarth::Util::RGBColorFilter* cf = asoeRGBColorFilter();
	if (!cf)
		return;
	osg::Vec3f c = cf->getRGBOffset();
	c.x() = v;
	cf->setRGBOffset(c);
	NotifyChanged("R");
}

float gEarthPack::oepRGBColorFilter::G::get()
{
	osgEarth::Util::RGBColorFilter* cf = asoeRGBColorFilter();
	if (!cf)
		return 0.f;
	return cf->getRGBOffset().y();
}

void gEarthPack::oepRGBColorFilter::G::set(float v)
{
	osgEarth::Util::RGBColorFilter* cf = asoeRGBColorFilter();
	if (!cf)
		return;
	osg::Vec3f c = cf->getRGBOffset();
	c.y() = v;
	cf->setRGBOffset(c);
	NotifyChanged("G");
}

float gEarthPack::oepRGBColorFilter::B::get()
{
	osgEarth::Util::RGBColorFilter* cf = asoeRGBColorFilter();
	if (!cf)
		return 0.f;
	return cf->getRGBOffset().z();
}

void gEarthPack::oepRGBColorFilter::B::set(float v)
{
	osgEarth::Util::RGBColorFilter* cf = asoeRGBColorFilter();
	if (!cf)
		return;
	osg::Vec3f c = cf->getRGBOffset();
	c.z() = v;
	cf->setRGBOffset(c);
	NotifyChanged("B");
}
