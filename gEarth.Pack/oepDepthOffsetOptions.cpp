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
	if (as<osgEarth::DepthOffsetOptions>()->enabled().isSet())
		return false;
	return as<osgEarth::DepthOffsetOptions>()->enabled().value();
}

void oepDepthOffsetOptions::Enabled::set(bool p)
{
	as<osgEarth::DepthOffsetOptions>()->enabled() = p;
	NotifyChanged("Enabled");
}

double oepDepthOffsetOptions::MinBias::get()
{
	if (as<osgEarth::DepthOffsetOptions>()->minBias().isSet())
		return 0.0;
	return as<osgEarth::DepthOffsetOptions>()->minBias().value().getValue();
}

void oepDepthOffsetOptions::MinBias::set(double p)
{
	as<osgEarth::DepthOffsetOptions>()->minBias() = p;
	NotifyChanged("MinBias");
}

double oepDepthOffsetOptions::MaxBias::get()
{
	if (as<osgEarth::DepthOffsetOptions>()->maxBias().isSet())
		return 0.0;
	return as<osgEarth::DepthOffsetOptions>()->maxBias().value().getValue();
}

void oepDepthOffsetOptions::MaxBias::set(double p)
{
	as<osgEarth::DepthOffsetOptions>()->maxBias() = p;
	NotifyChanged("MaxBias");
}

double oepDepthOffsetOptions::MinRange::get()
{
	if (as<osgEarth::DepthOffsetOptions>()->minRange().isSet())
		return 0.0;
	return as<osgEarth::DepthOffsetOptions>()->minRange().value().getValue();
}

void oepDepthOffsetOptions::MinRange::set(double p)
{
	as<osgEarth::DepthOffsetOptions>()->minRange() = p;
	NotifyChanged("MinRange");
}

double oepDepthOffsetOptions::MaxRange::get()
{
	if (as<osgEarth::DepthOffsetOptions>()->maxRange().isSet())
		return 0.0;
	return as<osgEarth::DepthOffsetOptions>()->maxRange().value().getValue();
}

void oepDepthOffsetOptions::MaxRange::set(double p)
{
	as<osgEarth::DepthOffsetOptions>()->maxRange() = p;
	NotifyChanged("MaxRange");
}

bool oepDepthOffsetOptions::Automatic::get()
{
	if (as<osgEarth::DepthOffsetOptions>()->automatic().isSet())
		return false;
	return as<osgEarth::DepthOffsetOptions>()->automatic().value();
}

void oepDepthOffsetOptions::Automatic::set(bool p)
{
	as<osgEarth::DepthOffsetOptions>()->automatic() = p;
	NotifyChanged("Automatic");
}
