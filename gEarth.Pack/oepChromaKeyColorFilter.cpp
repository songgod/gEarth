#include "stdafx.h"
#include "oepChromaKeyColorFilter.h"

using namespace gEarthPack;

oepChromaKeyColorFilter::oepChromaKeyColorFilter()
{
	setRef(new osgEarth::Util::ChromaKeyColorFilter());
}

void oepChromaKeyColorFilter::Reset()
{
	osgEarth::Util::ChromaKeyColorFilter* cf = as<osgEarth::Util::ChromaKeyColorFilter>();
	if (!cf)
		return;
	cf->setColor(osg::Vec3f(0, 0, 0));
	cf->setDistance(0);
}

oepVec3f oepChromaKeyColorFilter::Color::get()
{
	osgEarth::Util::ChromaKeyColorFilter* cf = as<osgEarth::Util::ChromaKeyColorFilter>();
	if (!cf)
		return oepVec3f();
	return oepVec3f(cf->getColor());
}

void oepChromaKeyColorFilter::Color::set(oepVec3f v)
{
	osgEarth::Util::ChromaKeyColorFilter* cf = as<osgEarth::Util::ChromaKeyColorFilter>();
	if (!cf)
		return;
	cf->setColor(osg::Vec3f(v.x, v.y, v.z));
	NotifyChanged("Color");
}

float oepChromaKeyColorFilter::Distance::get()
{
	osgEarth::Util::ChromaKeyColorFilter* cf = as<osgEarth::Util::ChromaKeyColorFilter>();
	if (!cf)
		return 0.0;
	return cf->getDistance();
}

void oepChromaKeyColorFilter::Distance::set(float v)
{
	osgEarth::Util::ChromaKeyColorFilter* cf = as<osgEarth::Util::ChromaKeyColorFilter>();
	if (!cf)
		return;
	cf->setDistance(v);
	NotifyChanged("Distance");
}

float oepChromaKeyColorFilter::R::get()
{
	osgEarth::Util::ChromaKeyColorFilter* cf = as<osgEarth::Util::ChromaKeyColorFilter>();
	if (!cf)
		return 0.f;
	return cf->getColor().x();
}

void oepChromaKeyColorFilter::R::set(float v)
{
	osgEarth::Util::ChromaKeyColorFilter* cf = as<osgEarth::Util::ChromaKeyColorFilter>();
	if (!cf)
		return;
	osg::Vec3f c = cf->getColor();
	c.x() = v;
	cf->setColor(c);
	NotifyChanged("R");
}

float oepChromaKeyColorFilter::G::get()
{
	osgEarth::Util::ChromaKeyColorFilter* cf = as<osgEarth::Util::ChromaKeyColorFilter>();
	if (!cf)
		return 0.f;
	return cf->getColor().y();
}

void oepChromaKeyColorFilter::G::set(float v)
{
	osgEarth::Util::ChromaKeyColorFilter* cf = as<osgEarth::Util::ChromaKeyColorFilter>();
	if (!cf)
		return;
	osg::Vec3f c = cf->getColor();
	c.y() = v;
	cf->setColor(c);
	NotifyChanged("G");
}

float oepChromaKeyColorFilter::B::get()
{
	osgEarth::Util::ChromaKeyColorFilter* cf = as<osgEarth::Util::ChromaKeyColorFilter>();
	if (!cf)
		return 0.f;
	return cf->getColor().z();
}

void oepChromaKeyColorFilter::B::set(float v)
{
	osgEarth::Util::ChromaKeyColorFilter* cf = as<osgEarth::Util::ChromaKeyColorFilter>();
	if (!cf)
		return;
	osg::Vec3f c = cf->getColor();
	c.z() = v;
	cf->setColor(c);
	NotifyChanged("B");
}
