#include "stdafx.h"
#include "oepCMYKColorFilter.h"

using namespace gEarthPack;

oepCMYKColorFilter::oepCMYKColorFilter()
{
	_handle = new ColorFilterHandle(new osgEarth::Util::CMYKColorFilter());
}

osgEarth::Util::CMYKColorFilter* oepCMYKColorFilter::asoCMYKColorFilter()
{
	return dynamic_cast<osgEarth::Util::CMYKColorFilter*>(_handle->getValue());
}

void oepCMYKColorFilter::Reset()
{
	osgEarth::Util::CMYKColorFilter* cf = asoCMYKColorFilter();
	if (!cf)
		return;
	cf->setCMYKOffset(osg::Vec4f(0, 0, 0, 0));
}

oepVec4f oepCMYKColorFilter::Offset::get()
{
	osgEarth::Util::CMYKColorFilter* cf = asoCMYKColorFilter();
	if (!cf)
		return oepVec4f();
	return oepVec4f(cf->getCMYKOffset());
}

void oepCMYKColorFilter::Offset::set(oepVec4f v)
{
	osgEarth::Util::CMYKColorFilter* cf = asoCMYKColorFilter();
	if (!cf)
		return;
	cf->setCMYKOffset(osg::Vec4f(v.x, v.y, v.z,v.a));
	NotifyChanged("Offset");
}

float oepCMYKColorFilter::C::get()
{
	osgEarth::Util::CMYKColorFilter* cf = asoCMYKColorFilter();
	if (!cf)
		return 0.f;
	return cf->getCMYKOffset().x();
}

void oepCMYKColorFilter::C::set(float v)
{
	osgEarth::Util::CMYKColorFilter* cf = asoCMYKColorFilter();
	if (!cf)
		return;
	osg::Vec4f c = cf->getCMYKOffset();
	c.x() = v;
	cf->setCMYKOffset(c);
	NotifyChanged("C");
}

float oepCMYKColorFilter::M::get()
{
	osgEarth::Util::CMYKColorFilter* cf = asoCMYKColorFilter();
	if (!cf)
		return 0.f;
	return cf->getCMYKOffset().y();
}

void oepCMYKColorFilter::M::set(float v)
{
	osgEarth::Util::CMYKColorFilter* cf = asoCMYKColorFilter();
	if (!cf)
		return;
	osg::Vec4f c = cf->getCMYKOffset();
	c.y() = v;
	cf->setCMYKOffset(c);
	NotifyChanged("M");
}

float oepCMYKColorFilter::Y::get()
{
	osgEarth::Util::CMYKColorFilter* cf = asoCMYKColorFilter();
	if (!cf)
		return 0.f;
	return cf->getCMYKOffset().z();
}

void oepCMYKColorFilter::Y::set(float v)
{
	osgEarth::Util::CMYKColorFilter* cf = asoCMYKColorFilter();
	if (!cf)
		return;
	osg::Vec4f c = cf->getCMYKOffset();
	c.z() = v;
	cf->setCMYKOffset(c);
	NotifyChanged("Y");
}

float oepCMYKColorFilter::K::get()
{
	osgEarth::Util::CMYKColorFilter* cf = asoCMYKColorFilter();
	if (!cf)
		return 0.f;
	return cf->getCMYKOffset().z();
}

void oepCMYKColorFilter::K::set(float v)
{
	osgEarth::Util::CMYKColorFilter* cf = asoCMYKColorFilter();
	if (!cf)
		return;
	osg::Vec4f c = cf->getCMYKOffset();
	c.a() = v;
	cf->setCMYKOffset(c);
	NotifyChanged("K");
}
