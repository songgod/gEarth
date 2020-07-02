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
	return ntFadeOptions()->duration().value();
}

void oepFadeOptions::Duration::set(float p)
{
	ntFadeOptions()->duration() = p;
	NotifyChanged("Duration");
}

float oepFadeOptions::MaxRange::get()
{
	return ntFadeOptions()->maxRange().value();
}

void oepFadeOptions::MaxRange::set(float p)
{
	ntFadeOptions()->maxRange() = p;
	NotifyChanged("MaxRange");
}

float oepFadeOptions::AttenuationDistance::get()
{
	return ntFadeOptions()->attenuationDistance().value();
}

void oepFadeOptions::AttenuationDistance::set(float p)
{
	ntFadeOptions()->attenuationDistance() = p;
	NotifyChanged("AttenuationDistance");
}
