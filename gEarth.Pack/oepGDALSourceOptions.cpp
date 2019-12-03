#include "stdafx.h"
#include "oepGDALSourceOptions.h"

using namespace msclr::interop;
using namespace gEarthPack;

oepGDALSourceOptions::oepGDALSourceOptions()
{
	bind(new osgEarth::Drivers::GDALOptions(),true);
}

String^ oepGDALSourceOptions::url::get()
{
	return marshal_as<String^>(as<osgEarth::Drivers::GDALOptions>()->url()->full());
}

void oepGDALSourceOptions::url::set(String^ v)
{
	as<osgEarth::Drivers::GDALOptions>()->url() = marshal_as<std::string>(v);
}
