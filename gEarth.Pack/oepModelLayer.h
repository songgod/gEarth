#pragma once
#include "oepVisibleLayer.h"
#include "oepModelLayerOptions.h"

namespace gEarthPack
{
	public ref class oepModelLayer :
		public oepVisibleLayer
	{
	public:
		oepModelLayer(oepModelLayerOptions^ options);

	internal:

		oepModelLayer(osgEarth::ModelLayer* layer);
	};
}
