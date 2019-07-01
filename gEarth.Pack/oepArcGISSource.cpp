#include "stdafx.h"
#include "oepArcGISSource.h"
#include <osgEarthDrivers/arcgis/ArcGISOptions>
#include <msclr\marshal_cppstd.h>  

using namespace msclr::interop;
using namespace gEarthPack;

oepArcGISSource::oepArcGISSource()
{
	_handle = new osgEarth::Drivers::ArcGISOptions();
}

String^ gEarthPack::oepArcGISSource::url::get()
{
	return marshal_as<String^>(((osgEarth::Drivers::ArcGISOptions*)(_handle))->url()->getString());
}

void gEarthPack::oepArcGISSource::url::set(String^ v)
{
	((osgEarth::Drivers::ArcGISOptions*)(_handle))->url() = marshal_as<std::string>(v);
}

