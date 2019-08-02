#include "stdafx.h"
#include "oepConfigOptions.h"

using namespace gEarthPack;

oepConfigOptions::oepConfigOptions() :_handle(NULL)
{
}

oepConfigOptions::~oepConfigOptions()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

oepConfigOptions::!oepConfigOptions()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

osgEarth::ConfigOptions* oepConfigOptions::getoeConfigOptions()
{
	return _handle;
}
