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

	return ntBounds()->xMin();
}

void oepBounds::Xmin::set(double p)
{
	if (!Valid)
		return;

	ntBounds()->xMin()=p;
	NotifyChanged("Xmin");
	NotifyChanged("Width");
}

double oepBounds::Ymin::get()
{
	if (!Valid)
		return 0.0;

	return ntBounds()->yMin();
}

void oepBounds::Ymin::set(double p)
{
	if (!Valid)
		return;

	ntBounds()->yMin() = p;
	NotifyChanged("Ymin");
	NotifyChanged("Height");
}

double oepBounds::Zmin::get()
{
	if (!Valid)
		return 0.0;

	return ntBounds()->zMin();
}

void oepBounds::Zmin::set(double p)
{
	if (!Valid)
		return;

	ntBounds()->zMin() = p;
	NotifyChanged("Zmin");
	NotifyChanged("Depth");
}

double oepBounds::Xmax::get()
{
	if (!Valid)
		return 0.0;

	return ntBounds()->xMax();
}

void oepBounds::Xmax::set(double p)
{
	if (!Valid)
		return;

	ntBounds()->xMax() = p;
	NotifyChanged("Xmax");
	NotifyChanged("Width");
}

double oepBounds::Ymax::get()
{
	if (!Valid)
		return 0.0;

	return ntBounds()->yMax();
}

void oepBounds::Ymax::set(double p)
{
	if (!Valid)
		return;

	ntBounds()->yMax() = p;
	NotifyChanged("Ymax");
	NotifyChanged("Height");
}

double oepBounds::Zmax::get()
{
	if (!Valid)
		return 0.0;

	return ntBounds()->zMax();
}

void oepBounds::Zmax::set(double p)
{
	if (!Valid)
		return;

	ntBounds()->zMax() = p;
	NotifyChanged("Zmax");
	NotifyChanged("Depth");
}

double oepBounds::Width::get()
{
	if (!Valid)
		return 0.0;

	return ntBounds()->width();
}

double oepBounds::Height::get()
{
	if (!Valid)
		return 0.0;

	return ntBounds()->height();
}

double oepBounds::Depth::get()
{
	if (!Valid)
		return 0.0;

	return ntBounds()->depth();
}
