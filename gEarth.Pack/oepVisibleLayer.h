#pragma once
#include "oepLayer.h"
#include "oepVisibleLayerOptions.h"
#include <osgEarth/VisibleLayer>

namespace gEarthPack
{
	public ref class oepVisibleLayer : public oepLayer
	{
	public:
		oepVisibleLayer();

	public:

		property bool Visible
		{
			bool get();
			void set(bool v);
		}

	public:

		osgEarth::VisibleLayer* asoeVisibleLayer();
	};
}

