#include "stdafx.h"
#include "oepBingSourceOptions.h"

using namespace msclr::interop;
using namespace gEarthPack;

oepBingSourceOptions::oepBingSourceOptions()
{
	_handle = new osgEarth::Drivers::BingOptions();
}

String^ oepBingSourceOptions::apikey::get()
{
	return marshal_as<String^>(((osgEarth::Drivers::BingOptions*)(_handle))->apiKey().get());
}

void oepBingSourceOptions::apikey::set(String^ v)
{
	((osgEarth::Drivers::BingOptions*)(_handle))->apiKey() = marshal_as<std::string>(v);
	NotifyChanged("apikey");
}

String^ oepBingSourceOptions::imagerySet::get()
{
	return marshal_as<String^>(((osgEarth::Drivers::BingOptions*)(_handle))->imagerySet().get());
}

void oepBingSourceOptions::imagerySet::set(String^ v)
{
	((osgEarth::Drivers::BingOptions*)(_handle))->imagerySet() = marshal_as<std::string>(v);
	NotifyChanged("imagerySet");
}

String^ oepBingSourceOptions::imageryMetadataAPI::get()
{
	return marshal_as<String^>(((osgEarth::Drivers::BingOptions*)(_handle))->imageryMetadataAPI().get());
}

void oepBingSourceOptions::imageryMetadataAPI::set(String^ v)
{
	((osgEarth::Drivers::BingOptions*)(_handle))->imageryMetadataAPI() = marshal_as<std::string>(v);
	NotifyChanged("imageryMetadataAPI");
}
