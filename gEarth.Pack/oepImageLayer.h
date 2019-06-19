#pragma once
#include "oepTerrainLayer.h"
#include <osgEarth/ImageLayer>

namespace gEarthPack
{
	public ref class oepImageLayer : public oepTerrainLayer
	{
	public:
		oepImageLayer(oepTileSource^ source);

	public:

		osgEarth::ImageLayer* asoeImageLayer();
	};
}

