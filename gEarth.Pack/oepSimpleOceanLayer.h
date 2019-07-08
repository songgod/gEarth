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

	public:

		property oepVec4f Color
		{
			oepVec4f get();
			void set(oepVec4f v);
		}

		property float MaxAltitude
		{
			float get();
			void set(float v);
		}

	internal:
		oepSimpleOceanLayer(osgEarth::Util::SimpleOceanLayer* layer);
		osgEarth::Util::SimpleOceanLayer* asoeSimpleOceanLayer();
	};
}


