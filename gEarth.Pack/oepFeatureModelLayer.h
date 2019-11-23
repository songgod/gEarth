#pragma once
#include "oepVisibleLayer.h"
#include "oepFeatureModelLayerOptions.h"

namespace gEarthPack
{
	public ref class oepFeatureModelLayer :
		public oepVisibleLayer
	{
	public:
		oepFeatureModelLayer(oepFeatureModelLayerOptions^ options);

	internal:

		oepFeatureModelLayer(osgEarth::Features::FeatureModelLayer* layer);
	};
}