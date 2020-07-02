#include "stdafx.h"
#include "oepDepthOffsetOptions.h"

using namespace gEarthPack;
using namespace osgEarth;

oepDepthOffsetOptions::oepDepthOffsetOptions()
{
	bind(new DepthOffsetOptions(),true);
}

void gEarthPack::oepDepthOffsetOptions::delelehandle()
{
	del<osgEarth::DepthOffsetOptions>();
}

bool oepDepthOffsetOptions::Enabled::get()
{
	if (ntDepthOffsetOptions()->enabled().isSet())
		return false;
	return ntDepthOffsetOptions()->enabled().value();
}

void oepDepthOffsetOptions::Enabled::set(bool p)
{
	ntDepthOffsetOptions()->enabled() = p;
	NotifyChanged("Enabled");
}

double oepDepthOffsetOptions::MinBias::get()
{
	if (ntDepthOffsetOptions()->minBias().isSet())
		return 0.0;
	return ntDepthOffsetOptions()->minBias().value().getValue();
}

void oepDepthOffsetOptions::MinBias::set(double p)
{
	ntDepthOffsetOptions()->minBias() = p;
	NotifyChanged("MinBias");
}

double oepDepthOffsetOptions::MaxBias::get()
{
	if (ntDepthOffsetOptions()->maxBias().isSet())
		return 0.0;
	return ntDepthOffsetOptions()->maxBias().value().getValue();
}

void oepDepthOffsetOptions::MaxBias::set(double p)
{
	ntDepthOffsetOptions()->maxBias() = p;
	NotifyChanged("MaxBias");
}

double oepDepthOffsetOptions::MinRange::get()
{
	if (ntDepthOffsetOptions()->minRange().isSet())
		return 0.0;
	return ntDepthOffsetOptions()->minRange().value().getValue();
}

void oepDepthOffsetOptions::MinRange::set(double p)
{
	ntDepthOffsetOptions()->minRange() = p;
	NotifyChanged("MinRange");
}

double oepDepthOffsetOptions::MaxRange::get()
{
	if (ntDepthOffsetOptions()->maxRange().isSet())
		return 0.0;
	return ntDepthOffsetOptions()->maxRange().value().getValue();
}

void oepDepthOffsetOptions::MaxRange::set(double p)
{
	ntDepthOffsetOptions()->maxRange() = p;
	NotifyChanged("MaxRange");
}

bool oepDepthOffsetOptions::Automatic::get()
{
	if (ntDepthOffsetOptions()->automatic().isSet())
		return false;
	return ntDepthOffsetOptions()->automatic().value();
}

void oepDepthOffsetOptions::Automatic::set(bool p)
{
	ntDepthOffsetOptions()->automatic() = p;
	NotifyChanged("Automatic");
}
