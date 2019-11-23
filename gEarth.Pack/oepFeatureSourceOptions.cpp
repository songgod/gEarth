#include "stdafx.h"
#include "oepFeatureSourceOptions.h"

using namespace msclr::interop;
using namespace gEarthPack;

oepFeatureSourceOptions::oepFeatureSourceOptions()
{
	setVal(new osgEarth::Features::FeatureSourceOptions());
	_filters = gcnew oepConfigOptionsCollection();
}

String^ oepFeatureSourceOptions::Name::get()
{
	return marshal_as<String^>(as<osgEarth::Features::FeatureSourceOptions>()->name().value());
}

void oepFeatureSourceOptions::Name::set(String^ v)
{
	as<osgEarth::Features::FeatureSourceOptions>()->name() = marshal_as<std::string>(v);
	NotifyChanged("Name");
}

oepConfigOptionsCollection^ oepFeatureSourceOptions::Filters::get()
{
	return _filters;
}

void oepFeatureSourceOptions::Filters::set(oepConfigOptionsCollection^ v)
{
	_filters = v;
	NotifyChanged("Filters");
}

bool oepFeatureSourceOptions::OpenWrite::get()
{
	return as<osgEarth::Features::FeatureSourceOptions>()->openWrite().value();
}

void oepFeatureSourceOptions::OpenWrite::set(bool b)
{
	as<osgEarth::Features::FeatureSourceOptions>()->openWrite() = b;
	NotifyChanged("OpenWrite");
}

oepProfileOptions^ oepFeatureSourceOptions::Profile::get()
{
	return _profile;
}

void oepFeatureSourceOptions::Profile::set(oepProfileOptions^ profile)
{
	_profile = profile;
	if(profile!=nullptr)
		as<osgEarth::Features::FeatureSourceOptions>()->profile() = *(profile->val());
	NotifyChanged("Profile");
}

oepGeoInterpolation oepFeatureSourceOptions::GeoInterp::get()
{
	return _geoinerp;
}

void oepFeatureSourceOptions::GeoInterp::set(oepGeoInterpolation geoinerp)
{
	_geoinerp = geoinerp;
	as<osgEarth::Features::FeatureSourceOptions>()->geoInterp() = (osgEarth::GeoInterpolation)((int)geoinerp);
	NotifyChanged("GeoInterp");
}

String^ oepFeatureSourceOptions::FidAttribute::get()
{
	return marshal_as<String^>(as<osgEarth::Features::FeatureSourceOptions>()->fidAttribute().value());
}

void oepFeatureSourceOptions::FidAttribute::set(String^ v)
{
	as<osgEarth::Features::FeatureSourceOptions>()->fidAttribute() = marshal_as<std::string>(v);
	NotifyChanged("FidAttribute");
}