#include "stdafx.h"
#include "oepArcGISSource.h"
#include <osgEarthDrivers/arcgis/ArcGISOptions>
#include <msclr\marshal_cppstd.h>  

using namespace msclr::interop;
using namespace gEarthPack;

oepArcGISSource::oepArcGISSource()
{
	_handle = new osgEarth::Drivers::ArcGISOptions();
	url = "http://services.arcgisonline.com/arcgis/rest/services/World_Imagery/MapServer/";
}

String^ gEarthPack::oepArcGISSource::url::get()
{
	return marshal_as<String^>(((osgEarth::Drivers::ArcGISOptions*)(_handle))->url()->full());
}

void gEarthPack::oepArcGISSource::url::set(String^ v)
{
	((osgEarth::Drivers::ArcGISOptions*)(_handle))->url() = marshal_as<std::string>(v);
}

String^ gEarthPack::oepArcGISSource::token::get()
{
	return marshal_as<String^>(((osgEarth::Drivers::ArcGISOptions*)(_handle))->token().get());
}

void gEarthPack::oepArcGISSource::token::set(String^ v)
{
	((osgEarth::Drivers::ArcGISOptions*)(_handle))->token() = marshal_as<std::string>(v);
}

String^ gEarthPack::oepArcGISSource::format::get()
{
	return marshal_as<String^>(((osgEarth::Drivers::ArcGISOptions*)(_handle))->format().get());
}

void gEarthPack::oepArcGISSource::format::set(String^ v)
{
	((osgEarth::Drivers::ArcGISOptions*)(_handle))->format() = marshal_as<std::string>(v);
}

String^ gEarthPack::oepArcGISSource::layers::get()
{
	return marshal_as<String^>(((osgEarth::Drivers::ArcGISOptions*)(_handle))->layers().get());
}

void gEarthPack::oepArcGISSource::layers::set(String^ v)
{
	((osgEarth::Drivers::ArcGISOptions*)(_handle))->layers() = marshal_as<std::string>(v);
}
