#include "stdafx.h"
#include "oepColorFilter.h"

using namespace gEarthPack;

oepColorFilter::oepColorFilter() : _handle(NULL)
{
}

oepColorFilter::~oepColorFilter()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

oepColorFilter::!oepColorFilter()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

osgEarth::ColorFilter* oepColorFilter::asoeColorFilter()
{
	if (!_handle)
		return NULL;

	return _handle->getValue();
}
