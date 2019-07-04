#include "stdafx.h"
#include "oepColorFilter.h"

gEarthPack::oepColorFilter::oepColorFilter() : _handle(NULL)
{
}

gEarthPack::oepColorFilter::~oepColorFilter()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

gEarthPack::oepColorFilter::!oepColorFilter()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

osgEarth::ColorFilter* gEarthPack::oepColorFilter::asoeColorFilter()
{
	if (!_handle)
		return NULL;

	return _handle->getValue();
}
