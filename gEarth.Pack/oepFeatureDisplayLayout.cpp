#include "stdafx.h"
#include "oepFeatureDisplayLayout.h"

using namespace gEarthPack;

oepFeatureDisplayLayout::oepFeatureDisplayLayout()
{
	bind(new osgEarth::Features::FeatureDisplayLayout(), true);
}

void gEarthPack::oepFeatureDisplayLayout::delelehandle()
{
	del<osgEarth::Features::FeatureDisplayLayout>();
}
