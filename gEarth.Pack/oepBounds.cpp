#include "stdafx.h"
#include "oepBounds.h"

using namespace gEarthPack;

oepBounds::oepBounds()
{
	setVal(new osgEarth::Bounds());
}

oepBounds::oepBounds(const osgEarth::Bounds& bounds)
{
	setVal(new osgEarth::Bounds());
	setVal(bounds);
}

double oepBounds::Xmin::get()
{
	if (!Valid)
		return 0.0;

	return val()->xMin();
}

void oepBounds::Xmin::set(double p)
{
	if (!Valid)
		return;

	val()->xMin()=p;
	NotifyChanged("Xmin");
	NotifyChanged("Width");
}

double oepBounds::Ymin::get()
{
	if (!Valid)
		return 0.0;

	return val()->yMin();
}

void oepBounds::Ymin::set(double p)
{
	if (!Valid)
		return;

	val()->yMin() = p;
	NotifyChanged("Ymin");
	NotifyChanged("Height");
}

double oepBounds::Zmin::get()
{
	if (!Valid)
		return 0.0;

	return val()->zMin();
}

void oepBounds::Zmin::set(double p)
{
	if (!Valid)
		return;

	val()->zMin() = p;
	NotifyChanged("Zmin");
	NotifyChanged("Depth");
}

double oepBounds::Xmax::get()
{
	if (!Valid)
		return 0.0;

	return val()->xMax();
}

void oepBounds::Xmax::set(double p)
{
	if (!Valid)
		return;

	val()->xMax() = p;
	NotifyChanged("Xmax");
	NotifyChanged("Width");
}

double oepBounds::Ymax::get()
{
	if (!Valid)
		return 0.0;

	return val()->yMax();
}

void oepBounds::Ymax::set(double p)
{
	if (!Valid)
		return;

	val()->yMax() = p;
	NotifyChanged("Ymax");
	NotifyChanged("Height");
}

double oepBounds::Zmax::get()
{
	if (!Valid)
		return 0.0;

	return val()->zMax();
}

void oepBounds::Zmax::set(double p)
{
	if (!Valid)
		return;

	val()->zMax() = p;
	NotifyChanged("Zmax");
	NotifyChanged("Depth");
}

double oepBounds::Width::get()
{
	if (!Valid)
		return 0.0;

	return val()->width();
}

double oepBounds::Height::get()
{
	if (!Valid)
		return 0.0;

	return val()->height();
}

double oepBounds::Depth::get()
{
	if (!Valid)
		return 0.0;

	return val()->depth();
}
