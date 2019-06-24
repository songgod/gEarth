#include "stdafx.h"
#include "oepGDALSource.h"
#include <osgEarthDrivers/gdal/GDALOptions>
#include <msclr\marshal_cppstd.h>  

using namespace msclr::interop;
using namespace gEarthPack;

oepGDALSource::oepGDALSource()
{
	_handle = new osgEarth::Drivers::GDALOptions();
}

String^ gEarthPack::oepGDALSource::url::get()
{
	return marshal_as<String^>(((osgEarth::Drivers::GDALOptions*)(_handle))->url()->getString());
}

void gEarthPack::oepGDALSource::url::set(String^ v)
{
	((osgEarth::Drivers::GDALOptions*)(_handle))->url() = marshal_as<std::string>(v);
}
