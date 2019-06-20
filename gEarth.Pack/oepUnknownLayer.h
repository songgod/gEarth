#pragma once

#include "oepLayer.h"
#include <osgEarth/Layer>

namespace gEarthPack
{

	public ref class oepUnknownLayer : public oepLayer
	{
	public:
		oepUnknownLayer();

	internal:

		oepUnknownLayer(osgEarth::Layer* layer);
	};
}

