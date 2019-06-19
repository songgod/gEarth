#pragma once
#include "oepLayer.h"
#include <osgEarth/VisibleLayer>

namespace gEarthPack
{
	public ref class oepVisibleLayer : public oepLayer
	{
	public:
		oepVisibleLayer();
	public:

		osgEarth::VisibleLayer* asoeVisibleLayer();
	};
}

