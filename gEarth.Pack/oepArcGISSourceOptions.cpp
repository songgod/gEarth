#include "stdafx.h"
#include "oepArcGISSourceOptions.h"

using namespace msclr::interop;
using namespace gEarthPack;

oepArcGISSourceOptions::oepArcGISSourceOptions()
{
	setVal(new osgEarth::Drivers::ArcGISOptions());
	url = "http://services.arcgisonline.com/arcgis/rest/services/World_Imagery/MapServer/";
}

String^ oepArcGISSourceOptions::url::get()
{
	return marshal_as<String^>(((osgEarth::Drivers::ArcGISOptions*)(_handle))->url()->full());
}

void oepArcGISSourceOptions::url::set(String^ v)
{
	((osgEarth::Drivers::ArcGISOptions*)(_handle))->url() = marshal_as<std::string>(v);
}

String^ oepArcGISSourceOptions::token::get()
{
	return marshal_as<String^>(((osgEarth::Drivers::ArcGISOptions*)(_handle))->token().get());
}

void oepArcGISSourceOptions::token::set(String^ v)
{
	((osgEarth::Drivers::ArcGISOptions*)(_handle))->token() = marshal_as<std::string>(v);
}

String^ oepArcGISSourceOptions::format::get()
{
	return marshal_as<String^>(((osgEarth::Drivers::ArcGISOptions*)(_handle))->format().get());
}

void oepArcGISSourceOptions::format::set(String^ v)
{
	((osgEarth::Drivers::ArcGISOptions*)(_handle))->format() = marshal_as<std::string>(v);
}

String^ oepArcGISSourceOptions::layers::get()
{
	return marshal_as<String^>(((osgEarth::Drivers::ArcGISOptions*)(_handle))->layers().get());
}

void oepArcGISSourceOptions::layers::set(String^ v)
{
	((osgEarth::Drivers::ArcGISOptions*)(_handle))->layers() = marshal_as<std::string>(v);
}
