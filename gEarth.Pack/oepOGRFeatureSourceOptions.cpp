#include "stdafx.h"
#include "oepOGRFeatureSourceOptions.h"

using namespace msclr::interop;
using namespace gEarthPack;
using namespace osgEarth::Drivers;

oepOGRFeatureSourceOptions::oepOGRFeatureSourceOptions()
{
	bind(new OGRFeatureOptions(),true);
}

void gEarthPack::oepOGRFeatureSourceOptions::binded()
{
	_geometryConfig = gcnew oepConfig();
	_geometryConfig->bind(&(as<OGRFeatureOptions>()->geometryConfig().mutable_value()), false);
	_query = gcnew oepQuery();
	_query->bind(&(as<OGRFeatureOptions>()->query().mutable_value()), false);
}

void gEarthPack::oepOGRFeatureSourceOptions::unbinded()
{
	_geometryConfig->unbind();
	_query->unbind();
}

String^ oepOGRFeatureSourceOptions::Url::get()
{
	return marshal_as<String^>(as<OGRFeatureOptions>()->url()->full());
}

void oepOGRFeatureSourceOptions::Url::set(String^ p)
{
	as<OGRFeatureOptions>()->url() = marshal_as<std::string>(p);
}

String^ oepOGRFeatureSourceOptions::Connection::get()
{
	return marshal_as<String^>(as<OGRFeatureOptions>()->connection().value());
}

void oepOGRFeatureSourceOptions::Connection::set(String^ p)
{
	as<OGRFeatureOptions>()->connection() = marshal_as<std::string>(p);
}

String^ oepOGRFeatureSourceOptions::OgrDriver::get()
{
	return marshal_as<String^>(as<OGRFeatureOptions>()->ogrDriver().value());
}

void oepOGRFeatureSourceOptions::OgrDriver::set(String^ p)
{
	as<OGRFeatureOptions>()->ogrDriver() = marshal_as<std::string>(p);
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
	if (p != nullptr)
	{
		osgEarth::Config& cf = as<OGRFeatureOptions>()->geometryConfig().mutable_value();
		p->getVal(cf);
		p->bind(&cf,false);
	}
}

String^ oepOGRFeatureSourceOptions::GeometryUrl::get()
{
	return marshal_as<String^>(as<OGRFeatureOptions>()->geometryUrl().value());
}

void oepOGRFeatureSourceOptions::GeometryUrl::set(String^ p)
{
	as<OGRFeatureOptions>()->geometryUrl() = marshal_as<std::string>(p);
}

String^ oepOGRFeatureSourceOptions::Layer::get()
{
	return marshal_as<String^>(as<OGRFeatureOptions>()->layer().value());
}

void oepOGRFeatureSourceOptions::Layer::set(String^ p)
{
	as<OGRFeatureOptions>()->layer() = marshal_as<std::string>(p);
}

oepQuery^ oepOGRFeatureSourceOptions::Query::get()
{
	return _query;
}

void oepOGRFeatureSourceOptions::Query::set(oepQuery^ p)
{
	_query = p;
	if (p != nullptr)
	{
		osgEarth::Query& q = as<OGRFeatureOptions>()->query().mutable_value();
		p->getVal(q);
		p->bind(&q,false);
	}
}

