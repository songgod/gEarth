#include "stdafx.h"
#include "oepChromaKeyColorFilter.h"


gEarthPack::oepChromaKeyColorFilter::oepChromaKeyColorFilter()
{
	_handle = new ColorFilterHandle(new osgEarth::Util::ChromaKeyColorFilter());
}

osgEarth::Util::ChromaKeyColorFilter* gEarthPack::oepChromaKeyColorFilter::asoeChromaKeyColorFilter()
{
	return dynamic_cast<osgEarth::Util::ChromaKeyColorFilter*>(_handle->getValue());
}

gEarthPack::oepVec3f gEarthPack::oepChromaKeyColorFilter::Color::get()
{
	osgEarth::Util::ChromaKeyColorFilter* cf = asoeChromaKeyColorFilter();
	if (!cf)
		return oepVec3f();
	return oepVec3f(cf->getColor());
}

void gEarthPack::oepChromaKeyColorFilter::Color::set(oepVec3f v)
{
	osgEarth::Util::ChromaKeyColorFilter* cf = asoeChromaKeyColorFilter();
	if (!cf)
		return;
	cf->setColor(osg::Vec3f(v.x, v.y, v.z));
	NotifyChanged("Color");
}

float gEarthPack::oepChromaKeyColorFilter::Distance::get()
{
	osgEarth::Util::ChromaKeyColorFilter* cf = asoeChromaKeyColorFilter();
	if (!cf)
		return 0.0;
	return cf->getDistance();
}

void gEarthPack::oepChromaKeyColorFilter::Distance::set(float v)
{
	osgEarth::Util::ChromaKeyColorFilter* cf = asoeChromaKeyColorFilter();
	if (!cf)
		return;
	cf->setDistance(v);
	NotifyChanged("Distance");
}

float gEarthPack::oepChromaKeyColorFilter::R::get()
{
	osgEarth::Util::ChromaKeyColorFilter* cf = asoeChromaKeyColorFilter();
	if (!cf)
		return 0.f;
	return cf->getColor().x();
}

void gEarthPack::oepChromaKeyColorFilter::R::set(float v)
{
	osgEarth::Util::ChromaKeyColorFilter* cf = asoeChromaKeyColorFilter();
	if (!cf)
		return;
	osg::Vec3f c = cf->getColor();
	c.x() = v;
	cf->setColor(c);
	NotifyChanged("R");
}

float gEarthPack::oepChromaKeyColorFilter::G::get()
{
	osgEarth::Util::ChromaKeyColorFilter* cf = asoeChromaKeyColorFilter();
	if (!cf)
		return 0.f;
	return cf->getColor().y();
}

void gEarthPack::oepChromaKeyColorFilter::G::set(float v)
{
	osgEarth::Util::ChromaKeyColorFilter* cf = asoeChromaKeyColorFilter();
	if (!cf)
		return;
	osg::Vec3f c = cf->getColor();
	c.y() = v;
	cf->setColor(c);
	NotifyChanged("G");
}

float gEarthPack::oepChromaKeyColorFilter::B::get()
{
	osgEarth::Util::ChromaKeyColorFilter* cf = asoeChromaKeyColorFilter();
	if (!cf)
		return 0.f;
	return cf->getColor().z();
}

void gEarthPack::oepChromaKeyColorFilter::B::set(float v)
{
	osgEarth::Util::ChromaKeyColorFilter* cf = asoeChromaKeyColorFilter();
	if (!cf)
		return;
	osg::Vec3f c = cf->getColor();
	c.z() = v;
	cf->setColor(c);
	NotifyChanged("B");
}
