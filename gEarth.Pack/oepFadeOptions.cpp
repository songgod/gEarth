#include "stdafx.h"
#include "oepFadeOptions.h"

using namespace gEarthPack;
using namespace osgEarth;

oepFadeOptions::oepFadeOptions()
{
	bind(new FadeOptions(), true);
}

void gEarthPack::oepFadeOptions::delelehandle()
{
	del<osgEarth::FadeOptions>();
}

float oepFadeOptions::Duration::get()
{
	return as<osgEarth::FadeOptions>()->duration().value();
}

void oepFadeOptions::Duration::set(float p)
{
	as<osgEarth::FadeOptions>()->duration() = p;
	NotifyChanged("Duration");
}

float oepFadeOptions::MaxRange::get()
{
	return as<osgEarth::FadeOptions>()->maxRange().value();
}

void oepFadeOptions::MaxRange::set(float p)
{
	as<osgEarth::FadeOptions>()->maxRange() = p;
	NotifyChanged("MaxRange");
}

float oepFadeOptions::AttenuationDistance::get()
{
	return as<osgEarth::FadeOptions>()->attenuationDistance().value();
}

void oepFadeOptions::AttenuationDistance::set(float p)
{
	as<osgEarth::FadeOptions>()->attenuationDistance() = p;
	NotifyChanged("AttenuationDistance");
}
