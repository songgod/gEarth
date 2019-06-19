#include "stdafx.h"
#include "oepSource.h"

using namespace gEarthPack;

oepSource::oepSource():_handle(NULL)
{
}

gEarthPack::oepSource::~oepSource()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

gEarthPack::oepSource::!oepSource()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

osgEarth::ConfigOptions* gEarthPack::oepSource::getoeConfigOptions()
{
	return _handle;
}
