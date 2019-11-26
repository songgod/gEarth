#include "stdafx.h"
#include "oepOGRFeatureSourceOptions.h"

using namespace msclr::interop;
using namespace gEarthPack;

oepOGRFeatureSourceOptions::oepOGRFeatureSourceOptions()
{
	setVal(new osgEarth::Drivers::OGRFeatureOptions());
}

String^ oepOGRFeatureSourceOptions::Url::get()
{
	return marshal_as<String^>(as<osgEarth::Drivers::OGRFeatureOptions>()->url()->full());
}

void oepOGRFeatureSourceOptions::Url::set(String^ p)
{
	as<osgEarth::Drivers::OGRFeatureOptions>()->url() = marshal_as<std::string>(p);
}

String^ oepOGRFeatureSourceOptions::Connection::get()
{
	return marshal_as<String^>(as<osgEarth::Drivers::OGRFeatureOptions>()->connection().value());
}

void oepOGRFeatureSourceOptions::Connection::set(String^ p)
{
	as<osgEarth::Drivers::OGRFeatureOptions>()->connection() = marshal_as<std::string>(p);
}

String^ oepOGRFeatureSourceOptions::OgrDriver::get()
{
	return marshal_as<String^>(as<osgEarth::Drivers::OGRFeatureOptions>()->ogrDriver().value());
}

void oepOGRFeatureSourceOptions::OgrDriver::set(String^ p)
{
	as<osgEarth::Drivers::OGRFeatureOptions>()->ogrDriver() = marshal_as<std::string>(p);
}

bool oepOGRFeatureSourceOptions::BuildSpatialIndex::get()
{
	return as<osgEarth::Drivers::OGRFeatureOptions>()->buildSpatialIndex().value();
}

void oepOGRFeatureSourceOptions::BuildSpatialIndex::set(bool p)
{
	as<osgEarth::Drivers::OGRFeatureOptions>()->buildSpatialIndex() = p;
}

bool oepOGRFeatureSourceOptions::ForceRebuildSpatialIndex::get()
{
	return as<osgEarth::Drivers::OGRFeatureOptions>()->forceRebuildSpatialIndex().value();
}

void oepOGRFeatureSourceOptions::ForceRebuildSpatialIndex::set(bool p)
{
	as<osgEarth::Drivers::OGRFeatureOptions>()->forceRebuildSpatialIndex() = p;
}

oepConfig^ oepOGRFeatureSourceOptions::GeometryConfig::get()
{
	return _geometryConfig;
}

void oepOGRFeatureSourceOptions::GeometryConfig::set(oepConfig^ p)
{
	_geometryConfig = p;
	if(p!=nullptr)
		as<osgEarth::Drivers::OGRFeatureOptions>()->geometryConfig() = *(p->val());
}

String^ oepOGRFeatureSourceOptions::GeometryUrl::get()
{
	return marshal_as<String^>(as<osgEarth::Drivers::OGRFeatureOptions>()->geometryUrl().value());
}

void oepOGRFeatureSourceOptions::GeometryUrl::set(String^ p)
{
	as<osgEarth::Drivers::OGRFeatureOptions>()->geometryUrl() = marshal_as<std::string>(p);
}

String^ oepOGRFeatureSourceOptions::Layer::get()
{
	return marshal_as<String^>(as<osgEarth::Drivers::OGRFeatureOptions>()->layer().value());
}

void oepOGRFeatureSourceOptions::Layer::set(String^ p)
{
	as<osgEarth::Drivers::OGRFeatureOptions>()->layer() = marshal_as<std::string>(p);
}

oepQuery^ oepOGRFeatureSourceOptions::Query::get()
{
	return _query;
}

void oepOGRFeatureSourceOptions::Query::set(oepQuery^ p)
{
	_query = p;
	if(p)
		as<osgEarth::Drivers::OGRFeatureOptions>()->query() = *(p->val());
}
