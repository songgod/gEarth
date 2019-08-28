#include "stdafx.h"
#include "oepVisibleLayer.h"
#include <osgEarth/VisibleLayer>

using namespace gEarthPack;
oepVisibleLayer::oepVisibleLayer()
{
}

osgEarth::VisibleLayer* oepVisibleLayer::asoeVisibleLayer()
{
	return dynamic_cast<osgEarth::VisibleLayer*>(_handle->getValue());
}

bool oepVisibleLayer::Visible::get()
{
	osgEarth::VisibleLayer* plyr = asoeVisibleLayer();
	if (plyr == nullptr)
		return false;
	return plyr->getVisible() ? true : false;
}

void oepVisibleLayer::Visible::set(bool v)
{
	osgEarth::VisibleLayer* plyr = asoeVisibleLayer();
	if (plyr == nullptr)
		return;

	plyr->setVisible(v ? true : false);
	NotifyChanged("Visible");
}
