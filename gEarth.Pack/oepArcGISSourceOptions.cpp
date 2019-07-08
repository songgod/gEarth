#include "stdafx.h"
#include "oepArcGISSourceOptions.h"
#include <osgEarthDrivers/arcgis/ArcGISOptions>
#include <msclr\marshal_cppstd.h>  

using namespace msclr::interop;
using namespace gEarthPack;

oepArcGISSourceOptions::oepArcGISSourceOptions()
{
	_handle = new osgEarth::Drivers::ArcGISOptions();
	url = "http://services.arcgisonline.com/arcgis/rest/services/World_Imagery/MapServer/";
}

String^ gEarthPack::oepArcGISSourceOptions::url::get()
{
	return marshal_as<String^>(((osgEarth::Drivers::ArcGISOptions*)(_handle))->url()->full());
}

void gEarthPack::oepArcGISSourceOptions::url::set(String^ v)
{
	((osgEarth::Drivers::ArcGISOptions*)(_handle))->url() = marshal_as<std::string>(v);
}

String^ gEarthPack::oepArcGISSourceOptions::token::get()
{
	return marshal_as<String^>(((osgEarth::Drivers::ArcGISOptions*)(_handle))->token().get());
}

void gEarthPack::oepArcGISSourceOptions::token::set(String^ v)
{
	((osgEarth::Drivers::ArcGISOptions*)(_handle))->token() = marshal_as<std::string>(v);
}

String^ gEarthPack::oepArcGISSourceOptions::format::get()
{
	return marshal_as<String^>(((osgEarth::Drivers::ArcGISOptions*)(_handle))->format().get());
}

void gEarthPack::oepArcGISSourceOptions::format::set(String^ v)
{
	((osgEarth::Drivers::ArcGISOptions*)(_handle))->format() = marshal_as<std::string>(v);
}

String^ gEarthPack::oepArcGISSourceOptions::layers::get()
{
	return marshal_as<String^>(((osgEarth::Drivers::ArcGISOptions*)(_handle))->layers().get());
}

void gEarthPack::oepArcGISSourceOptions::layers::set(String^ v)
{
	((osgEarth::Drivers::ArcGISOptions*)(_handle))->layers() = marshal_as<std::string>(v);
}
