#include "stdafx.h"
#include "oepBounds.h"

using namespace gEarthPack;

oepBounds::oepBounds()
{
	bind(new osgEarth::Bounds(),true);
}

void gEarthPack::oepBounds::delelehandle()
{
	del<osgEarth::Bounds>();
}

double oepBounds::Xmin::get()
{
	if (!Valid)
		return 0.0;

	return as<osgEarth::Bounds>()->xMin();
}

void oepBounds::Xmin::set(double p)
{
	if (!Valid)
		return;

	as<osgEarth::Bounds>()->xMin()=p;
	NotifyChanged("Xmin");
	NotifyChanged("Width");
}

double oepBounds::Ymin::get()
{
	if (!Valid)
		return 0.0;

	return as<osgEarth::Bounds>()->yMin();
}

void oepBounds::Ymin::set(double p)
{
	if (!Valid)
		return;

	as<osgEarth::Bounds>()->yMin() = p;
	NotifyChanged("Ymin");
	NotifyChanged("Height");
}

double oepBounds::Zmin::get()
{
	if (!Valid)
		return 0.0;

	return as<osgEarth::Bounds>()->zMin();
}

void oepBounds::Zmin::set(double p)
{
	if (!Valid)
		return;

	as<osgEarth::Bounds>()->zMin() = p;
	NotifyChanged("Zmin");
	NotifyChanged("Depth");
}

double oepBounds::Xmax::get()
{
	if (!Valid)
		return 0.0;

	return as<osgEarth::Bounds>()->xMax();
}

void oepBounds::Xmax::set(double p)
{
	if (!Valid)
		return;

	as<osgEarth::Bounds>()->xMax() = p;
	NotifyChanged("Xmax");
	NotifyChanged("Width");
}

double oepBounds::Ymax::get()
{
	if (!Valid)
		return 0.0;

	return as<osgEarth::Bounds>()->yMax();
}

void oepBounds::Ymax::set(double p)
{
	if (!Valid)
		return;

	as<osgEarth::Bounds>()->yMax() = p;
	NotifyChanged("Ymax");
	NotifyChanged("Height");
}

double oepBounds::Zmax::get()
{
	if (!Valid)
		return 0.0;

	return as<osgEarth::Bounds>()->zMax();
}

void oepBounds::Zmax::set(double p)
{
	if (!Valid)
		return;

	as<osgEarth::Bounds>()->zMax() = p;
	NotifyChanged("Zmax");
	NotifyChanged("Depth");
}

double oepBounds::Width::get()
{
	if (!Valid)
		return 0.0;

	return as<osgEarth::Bounds>()->width();
}

double oepBounds::Height::get()
{
	if (!Valid)
		return 0.0;

	return as<osgEarth::Bounds>()->height();
}

double oepBounds::Depth::get()
{
	if (!Valid)
		return 0.0;

	return as<osgEarth::Bounds>()->depth();
}
