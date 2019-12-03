#include "stdafx.h"
#include "oepFeatureSourceOptions.h"

using namespace gEarthPack;
using namespace osgEarth;
using namespace osgEarth::Features;
using namespace msclr::interop;

oepFeatureSourceOptions::oepFeatureSourceOptions():_profile(nullptr), _filters(nullptr)
{
	bind(new FeatureSourceOptions(),true);
}

void gEarthPack::oepFeatureSourceOptions::binded()
{
	_profile = gcnew oepProfileOptions();
	_profile->bind(&(as<FeatureSourceOptions>()->profile().mutable_value()), false);
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
	return marshal_as<String^>(as<FeatureSourceOptions>()->name().value());
}

void oepFeatureSourceOptions::Name::set(String^ v)
{
	as<FeatureSourceOptions>()->name() = marshal_as<std::string>(v);
	NotifyChanged("Name");
}

oepConfigOptionsCollection^ oepFeatureSourceOptions::Filters::get()
{
	return _filters;
}

void oepFeatureSourceOptions::Filters::set(oepConfigOptionsCollection^ v)
{
	_filters = v;

	std::vector<osgEarth::ConfigOptions>& coptions = as<FeatureSourceOptions>()->filters();
	_filters->getVal(coptions);
	_filters->bind(&coptions,false);
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
	ProfileOptions &ops = as<FeatureSourceOptions>()->profile().mutable_value();
	_profile->getVal(ops);
	_profile->bind(&ops,false);
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
	return marshal_as<String^>(as<FeatureSourceOptions>()->fidAttribute().value());
}

void oepFeatureSourceOptions::FidAttribute::set(String^ v)
{
	as<FeatureSourceOptions>()->fidAttribute() = marshal_as<std::string>(v);
	NotifyChanged("FidAttribute");
}