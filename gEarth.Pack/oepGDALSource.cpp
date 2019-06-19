#include "stdafx.h"
#include "oepGDALSource.h"
#include <osgEarthDrivers/gdal/GDALOptions>
using namespace gEarthPack;

oepGDALSource::oepGDALSource()
{
	_handle = new osgEarth::Drivers::GDALOptions();
}
