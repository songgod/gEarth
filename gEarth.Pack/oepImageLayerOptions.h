#pragma once
#include "oepTerrainLayerOptions.h"

namespace gEarthPack
{
	public ref class oepImageLayerOptions :
		public oepTerrainLayerOptions
	{
	public:
		oepImageLayerOptions();

	internal:

		osgEarth::ImageLayerOptions* asoeImageLayerOptions();
	};
}
