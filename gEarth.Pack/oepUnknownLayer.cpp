#include "stdafx.h"
#include "oepUnknownLayer.h"

using namespace gEarthPack;

oepUnknownLayer::oepUnknownLayer()
{
}

oepUnknownLayer::oepUnknownLayer(osgEarth::Layer* layer)
{
	_handle->setValue(layer);
}

bool oepUnknownLayer::Visible::get()
{
	osgEarth::VisibleLayer* plyr = as<osgEarth::VisibleLayer>();
	if (plyr == nullptr)
		return false;
	return plyr->getVisible() ? true : false;
}

void oepUnknownLayer::Visible::set(bool v)
{
	osgEarth::VisibleLayer* plyr = as<osgEarth::VisibleLayer>();
	if (plyr == nullptr)
		return;

	plyr->setVisible(v ? true : false);
	NotifyChanged("Visible");
}