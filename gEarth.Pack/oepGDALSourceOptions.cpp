#include "stdafx.h"
#include "oepGDALSourceOptions.h"


using namespace gEarthPack;

oepGDALSourceOptions::oepGDALSourceOptions()
{
	bind(new osgEarth::Drivers::GDALOptions(),true);
}

String^ oepGDALSourceOptions::url::get()
{
	return Str2Cli(as<osgEarth::Drivers::GDALOptions>()->url()->full());
}

void oepGDALSourceOptions::url::set(String^ v)
{
	as<osgEarth::Drivers::GDALOptions>()->url() = Str2Std(v);
}
