#include "stdafx.h"
#include "oepVisibleLayer.h"
#include <osgEarth/VisibleLayer>

using namespace gEarthPack;
oepVisibleLayer::oepVisibleLayer()
{
}

bool oepVisibleLayer::Visible::get()
{
	osgEarth::VisibleLayer* plyr = as<osgEarth::VisibleLayer>();
	if (plyr == nullptr)
		return false;
	return plyr->getVisible() ? true : false;
}

void oepVisibleLayer::Visible::set(bool v)
{
	osgEarth::VisibleLayer* plyr = as<osgEarth::VisibleLayer>();
	if (plyr == nullptr)
		return;

	plyr->setVisible(v ? true : false);
	NotifyChanged("Visible");
}
