#include "stdafx.h"
#include "oepBingSourceOptions.h"


using namespace gEarthPack;

oepBingSourceOptions::oepBingSourceOptions()
{
	bind(new osgEarth::Drivers::BingOptions(),true);
}

String^ oepBingSourceOptions::apikey::get()
{
	return Str2Cli(((osgEarth::Drivers::BingOptions*)(_handle))->apiKey().get());
}

void oepBingSourceOptions::apikey::set(String^ v)
{
	((osgEarth::Drivers::BingOptions*)(_handle))->apiKey() = Str2Std(v);
	NotifyChanged("apikey");
}

String^ oepBingSourceOptions::imagerySet::get()
{
	return Str2Cli(((osgEarth::Drivers::BingOptions*)(_handle))->imagerySet().get());
}

void oepBingSourceOptions::imagerySet::set(String^ v)
{
	((osgEarth::Drivers::BingOptions*)(_handle))->imagerySet() = Str2Std(v);
	NotifyChanged("imagerySet");
}

String^ oepBingSourceOptions::imageryMetadataAPI::get()
{
	return Str2Cli(((osgEarth::Drivers::BingOptions*)(_handle))->imageryMetadataAPI().get());
}

void oepBingSourceOptions::imageryMetadataAPI::set(String^ v)
{
	((osgEarth::Drivers::BingOptions*)(_handle))->imageryMetadataAPI() = Str2Std(v);
	NotifyChanged("imageryMetadataAPI");
}
