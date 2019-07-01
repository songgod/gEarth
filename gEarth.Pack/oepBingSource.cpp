#include "stdafx.h"
#include "oepBingSource.h"
#include <osgEarthDrivers/bing/BingOptions>
#include <msclr/marshal_cppstd.h>

using namespace msclr::interop;
using namespace gEarthPack;

oepBingSource::oepBingSource()
{
	_handle = new osgEarth::Drivers::BingOptions();
}

String^ gEarthPack::oepBingSource::apikey::get()
{
	return marshal_as<String^>(((osgEarth::Drivers::BingOptions*)(_handle))->apiKey().get());
}

void gEarthPack::oepBingSource::apikey::set(String^ v)
{
	((osgEarth::Drivers::BingOptions*)(_handle))->apiKey() = marshal_as<std::string>(v);
	NotifyChanged("apikey");
}

String^ gEarthPack::oepBingSource::imagerySet::get()
{
	return marshal_as<String^>(((osgEarth::Drivers::BingOptions*)(_handle))->imagerySet().get());
}

void gEarthPack::oepBingSource::imagerySet::set(String^ v)
{
	((osgEarth::Drivers::BingOptions*)(_handle))->imagerySet() = marshal_as<std::string>(v);
	NotifyChanged("imagerySet");
}

String^ gEarthPack::oepBingSource::imageryMetadataAPI::get()
{
	return marshal_as<String^>(((osgEarth::Drivers::BingOptions*)(_handle))->imageryMetadataAPI().get());
}

void gEarthPack::oepBingSource::imageryMetadataAPI::set(String^ v)
{
	((osgEarth::Drivers::BingOptions*)(_handle))->imageryMetadataAPI() = marshal_as<std::string>(v);
	NotifyChanged("imageryMetadataAPI");
}
