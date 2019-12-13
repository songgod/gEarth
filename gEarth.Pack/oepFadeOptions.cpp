#include "stdafx.h"
#include "oepFadeOptions.h"

using namespace gEarthPack;
using namespace osgEarth;

oepFadeOptions::oepFadeOptions()
{
	bind(new FadeOptions(), true);
}

float oepFadeOptions::Duration::get()
{
	return val()->duration().mutable_value();
}

void oepFadeOptions::Duration::set(float p)
{
	val()->duration() = p;
	NotifyChanged("Duration");
}

float oepFadeOptions::MaxRange::get()
{
	return val()->maxRange().mutable_value();
}

void oepFadeOptions::MaxRange::set(float p)
{
	val()->maxRange() = p;
	NotifyChanged("MaxRange");
}

float oepFadeOptions::AttenuationDistance::get()
{
	return val()->attenuationDistance().mutable_value();
}

void oepFadeOptions::AttenuationDistance::set(float p)
{
	val()->attenuationDistance() = p;
	NotifyChanged("AttenuationDistance");
}
