#include "stdafx.h"
#include "oepBingSourceOptions.h"
#include <osgEarthDrivers/bing/BingOptions>
#include <msclr/marshal_cppstd.h>

using namespace msclr::interop;
using namespace gEarthPack;

oepBingSourceOptions::oepBingSourceOptions()
{
	_handle = new osgEarth::Drivers::BingOptions();
}

String^ gEarthPack::oepBingSourceOptions::apikey::get()
{
	return marshal_as<String^>(((osgEarth::Drivers::BingOptions*)(_handle))->apiKey().get());
}

void gEarthPack::oepBingSourceOptions::apikey::set(String^ v)
{
	((osgEarth::Drivers::BingOptions*)(_handle))->apiKey() = marshal_as<std::string>(v);
	NotifyChanged("apikey");
}

String^ gEarthPack::oepBingSourceOptions::imagerySet::get()
{
	return marshal_as<String^>(((osgEarth::Drivers::BingOptions*)(_handle))->imagerySet().get());
}

void gEarthPack::oepBingSourceOptions::imagerySet::set(String^ v)
{
	((osgEarth::Drivers::BingOptions*)(_handle))->imagerySet() = marshal_as<std::string>(v);
	NotifyChanged("imagerySet");
}

String^ gEarthPack::oepBingSourceOptions::imageryMetadataAPI::get()
{
	return marshal_as<String^>(((osgEarth::Drivers::BingOptions*)(_handle))->imageryMetadataAPI().get());
}

void gEarthPack::oepBingSourceOptions::imageryMetadataAPI::set(String^ v)
{
	((osgEarth::Drivers::BingOptions*)(_handle))->imageryMetadataAPI() = marshal_as<std::string>(v);
	NotifyChanged("imageryMetadataAPI");
}
