#include "stdafx.h"
#include "oepVisibleLayer.h"

using namespace gEarthPack;
oepVisibleLayer::oepVisibleLayer()
{
}

osgEarth::VisibleLayer* gEarthPack::oepVisibleLayer::asoeVisibleLayer()
{
	return dynamic_cast<osgEarth::VisibleLayer*>(_handle->getValue());
}

bool gEarthPack::oepVisibleLayer::Visible::get()
{
	osgEarth::VisibleLayer* plyr = asoeVisibleLayer();
	if (plyr == nullptr)
		return false;
	return plyr->getVisible() ? true : false;
}

void gEarthPack::oepVisibleLayer::Visible::set(bool v)
{
	osgEarth::VisibleLayer* plyr = asoeVisibleLayer();
	if (plyr == nullptr)
		return;

	plyr->setVisible(v ? true : false);
	NotifyChanged("Visible");
}
