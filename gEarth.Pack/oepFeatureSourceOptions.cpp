#include "stdafx.h"
#include "oepFeatureSourceOptions.h"

using namespace gEarthPack;
using namespace osgEarth;
using namespace osgEarth::Features;


oepFeatureSourceOptions::oepFeatureSourceOptions():_profile(nullptr), _filters(nullptr)
{
	
}

void gEarthPack::oepFeatureSourceOptions::binded()
{
	_profile = gcnew oepProfileOptions();
	_profile->bind<osgEarth::ProfileOptions>(as<FeatureSourceOptions>()->profile(), false);
	_filters = gcnew oepConfigOptionsCollection();
	_filters->bind(&(as<FeatureSourceOptions>()->filters()), false);
}

void gEarthPack::oepFeatureSourceOptions::unbinded()
{
	_profile->unbind();
	_filters->unbind();
}

String^ oepFeatureSourceOptions::Name::get()
{
	return Str2Cli(as<FeatureSourceOptions>()->name().value());
}

void oepFeatureSourceOptions::Name::set(String^ v)
{
	as<FeatureSourceOptions>()->name() = Str2Std(v);
	NotifyChanged("Name");
}

oepConfigOptionsCollection^ oepFeatureSourceOptions::Filters::get()
{
	return _filters;
}

void oepFeatureSourceOptions::Filters::set(oepConfigOptionsCollection^ v)
{
	_filters = v;

	FeatureSourceOptions* to = as<FeatureSourceOptions>();
	if (to != NULL && _filters != nullptr)
	{
		to->filters() = *(_filters->Val());
	}
	NotifyChanged("Filters");
}

bool oepFeatureSourceOptions::OpenWrite::get()
{
	return as<FeatureSourceOptions>()->openWrite().value();
}

void oepFeatureSourceOptions::OpenWrite::set(bool b)
{
	as<FeatureSourceOptions>()->openWrite() = b;
	NotifyChanged("OpenWrite");
}

oepProfileOptions^ oepFeatureSourceOptions::Profile::get()
{
	return _profile;
}

void oepFeatureSourceOptions::Profile::set(oepProfileOptions^ profile)
{
	_profile = profile;
	FeatureSourceOptions* to = as<FeatureSourceOptions>();
	if (to != NULL && _profile!=nullptr)
	{
		to->profile() = *(_profile->as<ProfileOptions>());
	}
	NotifyChanged("Profile");
}

oepGeoInterpolation oepFeatureSourceOptions::GeoInterp::get()
{
	int v = as<FeatureSourceOptions>()->geoInterp().value();
	return v == 0 ? oepGeoInterpolation::GreatCircle : oepGeoInterpolation::RhumbLine;
}

void oepFeatureSourceOptions::GeoInterp::set(oepGeoInterpolation geoinerp)
{
	as<FeatureSourceOptions>()->geoInterp() = (osgEarth::GeoInterpolation)((int)geoinerp);
	NotifyChanged("GeoInterp");
}

String^ oepFeatureSourceOptions::FidAttribute::get()
{
	return Str2Cli(as<FeatureSourceOptions>()->fidAttribute().value());
}

void oepFeatureSourceOptions::FidAttribute::set(String^ v)
{
	as<FeatureSourceOptions>()->fidAttribute() = Str2Std(v);
	NotifyChanged("FidAttribute");
}