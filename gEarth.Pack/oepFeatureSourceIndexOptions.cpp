#include "stdafx.h"
#include "oepFeatureSourceIndexOptions.h"

using namespace gEarthPack;

oepFeatureSourceIndexOptions::oepFeatureSourceIndexOptions()
{
	bind(new osgEarth::Features::FeatureSourceIndexOptions(), true);
}

void gEarthPack::oepFeatureSourceIndexOptions::delelehandle()
{
	del<osgEarth::Features::FeatureSourceIndexOptions>();
}
