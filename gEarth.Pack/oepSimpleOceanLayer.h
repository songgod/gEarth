#pragma once
#include "oepVisibleLayer.h"
#include "oepVector.h"
#include "oepSimpleOceanLayerOptions.h"
#include <osgEarthUtil/SimpleOceanLayer>

namespace gEarthPack
{
	public ref class oepSimpleOceanLayer :
		public oepVisibleLayer
	{
	public:
		oepSimpleOceanLayer(oepSimpleOceanLayerOptions^ options);

	internal:
		oepSimpleOceanLayer(osgEarth::Util::SimpleOceanLayer* layer);
		osgEarth::Util::SimpleOceanLayer* asoeSimpleOceanLayer();
	};
}


