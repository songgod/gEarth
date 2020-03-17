#include "stdafx.h"
#include "oepOGRFeatureSourceOptions.h"


using namespace gEarthPack;
using namespace osgEarth::Drivers;

oepOGRFeatureSourceOptions::oepOGRFeatureSourceOptions()
{
	bind(new OGRFeatureOptions(),true);
}

void gEarthPack::oepOGRFeatureSourceOptions::binded()
{
	_geometryConfig = gcnew oepConfig();
	OGRFeatureOptions* o = as<OGRFeatureOptions>();
	_geometryConfig->bind(as<OGRFeatureOptions>()->geometryConfig(), false);
	_query = gcnew oepQuery();
	_query->bind(as<OGRFeatureOptions>()->query(), false);
}

void gEarthPack::oepOGRFeatureSourceOptions::unbinded()
{
	_geometryConfig->unbind();
	_query->unbind();
}

String^ oepOGRFeatureSourceOptions::Url::get()
{
	return Str2Cli(as<OGRFeatureOptions>()->url()->full());
}

void oepOGRFeatureSourceOptions::Url::set(String^ p)
{
	as<OGRFeatureOptions>()->url() = Str2Std(p);
}

String^ oepOGRFeatureSourceOptions::Connection::get()
{
	return Str2Cli(as<OGRFeatureOptions>()->connection().value());
}

void oepOGRFeatureSourceOptions::Connection::set(String^ p)
{
	as<OGRFeatureOptions>()->connection() = Str2Std(p);
}

String^ oepOGRFeatureSourceOptions::OgrDriver::get()
{
	return Str2Cli(as<OGRFeatureOptions>()->ogrDriver().value());
}

void oepOGRFeatureSourceOptions::OgrDriver::set(String^ p)
{
	as<OGRFeatureOptions>()->ogrDriver() = Str2Std(p);
}

bool oepOGRFeatureSourceOptions::BuildSpatialIndex::get()
{
	return as<OGRFeatureOptions>()->buildSpatialIndex().value();
}

void oepOGRFeatureSourceOptions::BuildSpatialIndex::set(bool p)
{
	as<OGRFeatureOptions>()->buildSpatialIndex() = p;
}

bool oepOGRFeatureSourceOptions::ForceRebuildSpatialIndex::get()
{
	return as<OGRFeatureOptions>()->forceRebuildSpatialIndex().value();
}

void oepOGRFeatureSourceOptions::ForceRebuildSpatialIndex::set(bool p)
{
	as<OGRFeatureOptions>()->forceRebuildSpatialIndex() = p;
}

oepConfig^ oepOGRFeatureSourceOptions::GeometryConfig::get()
{
	return _geometryConfig;
}

void oepOGRFeatureSourceOptions::GeometryConfig::set(oepConfig^ p)
{
	_geometryConfig = p;
	OGRFeatureOptions* to = as<OGRFeatureOptions>();
	if (to != NULL && _geometryConfig != nullptr)
	{
		to->geometryConfig() = *(_geometryConfig->as<Config>());
	}
}

String^ oepOGRFeatureSourceOptions::GeometryUrl::get()
{
	return Str2Cli(as<OGRFeatureOptions>()->geometryUrl().value());
}

void oepOGRFeatureSourceOptions::GeometryUrl::set(String^ p)
{
	as<OGRFeatureOptions>()->geometryUrl() = Str2Std(p);
}

String^ oepOGRFeatureSourceOptions::Layer::get()
{
	return Str2Cli(as<OGRFeatureOptions>()->layer().value());
}

void oepOGRFeatureSourceOptions::Layer::set(String^ p)
{
	as<OGRFeatureOptions>()->layer() = Str2Std(p);
}

oepQuery^ oepOGRFeatureSourceOptions::Query::get()
{
	return _query;
}

void oepOGRFeatureSourceOptions::Query::set(oepQuery^ p)
{
	_query = p;
	OGRFeatureOptions* to = as<OGRFeatureOptions>();
	if (to != NULL && _query != nullptr)
	{
		to->query() = *(_query->as<osgEarth::Query>());
	}
}

