#include "stdafx.h"
#include "oepDepthOffsetOptions.h"

using namespace gEarthPack;
using namespace osgEarth;

oepDepthOffsetOptions::oepDepthOffsetOptions()
{
	bind(new DepthOffsetOptions(),true);
}

bool oepDepthOffsetOptions::Enabled::get()
{
	if (val()->enabled().isSet())
		return false;
	return val()->enabled().value();
}

void oepDepthOffsetOptions::Enabled::set(bool p)
{
	val()->enabled() = p;
	NotifyChanged("Enabled");
}

double oepDepthOffsetOptions::MinBias::get()
{
	if (val()->minBias().isSet())
		return 0.0;
	return val()->minBias().value().getValue();
}

void oepDepthOffsetOptions::MinBias::set(double p)
{
	val()->minBias() = p;
	NotifyChanged("MinBias");
}

double oepDepthOffsetOptions::MaxBias::get()
{
	if (val()->maxBias().isSet())
		return 0.0;
	return val()->maxBias().value().getValue();
}

void oepDepthOffsetOptions::MaxBias::set(double p)
{
	val()->maxBias() = p;
	NotifyChanged("MaxBias");
}

double oepDepthOffsetOptions::MinRange::get()
{
	if (val()->minRange().isSet())
		return 0.0;
	return val()->minRange().value().getValue();
}

void oepDepthOffsetOptions::MinRange::set(double p)
{
	val()->minRange() = p;
	NotifyChanged("MinRange");
}

double oepDepthOffsetOptions::MaxRange::get()
{
	if (val()->maxRange().isSet())
		return 0.0;
	return val()->maxRange().value().getValue();
}

void oepDepthOffsetOptions::MaxRange::set(double p)
{
	val()->maxRange() = p;
	NotifyChanged("MaxRange");
}

bool oepDepthOffsetOptions::Automatic::get()
{
	if (val()->automatic().isSet())
		return false;
	return val()->automatic().value();
}

void oepDepthOffsetOptions::Automatic::set(bool p)
{
	val()->automatic() = p;
	NotifyChanged("Automatic");
}
