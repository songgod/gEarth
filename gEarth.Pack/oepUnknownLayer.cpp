#include "stdafx.h"
#include "oepUnknownLayer.h"
#include <osgEarth/VisibleLayer>

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
	osgEarth::VisibleLayer* plyr = dynamic_cast<osgEarth::VisibleLayer*>(_handle->getValue());
	if (plyr == nullptr)
		return false;
	return plyr->getVisible() ? true : false;
}

void oepUnknownLayer::Visible::set(bool v)
{
	osgEarth::VisibleLayer* plyr = dynamic_cast<osgEarth::VisibleLayer*>(_handle->getValue());
	if (plyr == nullptr)
		return;

	plyr->setVisible(v ? true : false);
	NotifyChanged("Visible");
}