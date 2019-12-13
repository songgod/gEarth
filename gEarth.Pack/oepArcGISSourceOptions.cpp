#include "stdafx.h"
#include "oepArcGISSourceOptions.h"


using namespace gEarthPack;

oepArcGISSourceOptions::oepArcGISSourceOptions()
{
	bind(new osgEarth::Drivers::ArcGISOptions(),true);
	url = "http://services.arcgisonline.com/arcgis/rest/services/World_Imagery/MapServer/";
}

String^ oepArcGISSourceOptions::url::get()
{
	return Str2Cli(((osgEarth::Drivers::ArcGISOptions*)(_handle))->url()->full());
}

void oepArcGISSourceOptions::url::set(String^ v)
{
	((osgEarth::Drivers::ArcGISOptions*)(_handle))->url() = Str2Std(v);
}

String^ oepArcGISSourceOptions::token::get()
{
	return Str2Cli(((osgEarth::Drivers::ArcGISOptions*)(_handle))->token().get());
}

void oepArcGISSourceOptions::token::set(String^ v)
{
	((osgEarth::Drivers::ArcGISOptions*)(_handle))->token() = Str2Std(v);
}

String^ oepArcGISSourceOptions::format::get()
{
	return Str2Cli(((osgEarth::Drivers::ArcGISOptions*)(_handle))->format().get());
}

void oepArcGISSourceOptions::format::set(String^ v)
{
	((osgEarth::Drivers::ArcGISOptions*)(_handle))->format() = Str2Std(v);
}

String^ oepArcGISSourceOptions::layers::get()
{
	return Str2Cli(((osgEarth::Drivers::ArcGISOptions*)(_handle))->layers().get());
}

void oepArcGISSourceOptions::layers::set(String^ v)
{
	((osgEarth::Drivers::ArcGISOptions*)(_handle))->layers() = Str2Std(v);
}
