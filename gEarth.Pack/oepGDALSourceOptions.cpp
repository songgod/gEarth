#include "stdafx.h"
#include "oepGDALSourceOptions.h"
#include <osgEarthDrivers/gdal/GDALOptions>
#include <msclr\marshal_cppstd.h>  

using namespace msclr::interop;
using namespace gEarthPack;

oepGDALSourceOptions::oepGDALSourceOptions()
{
	_handle = new osgEarth::Drivers::GDALOptions();
}

String^ gEarthPack::oepGDALSourceOptions::url::get()
{
	return marshal_as<String^>(((osgEarth::Drivers::GDALOptions*)(_handle))->url()->full());
}

void gEarthPack::oepGDALSourceOptions::url::set(String^ v)
{
	((osgEarth::Drivers::GDALOptions*)(_handle))->url() = marshal_as<std::string>(v);
}