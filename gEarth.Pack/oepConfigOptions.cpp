#include "stdafx.h"
#include "oepConfigOptions.h"


gEarthPack::oepConfigOptions::oepConfigOptions() :_handle(NULL)
{
}

gEarthPack::oepConfigOptions::~oepConfigOptions()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

gEarthPack::oepConfigOptions::!oepConfigOptions()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

osgEarth::ConfigOptions* gEarthPack::oepConfigOptions::getoeConfigOptions()
{
	return _handle;
}
