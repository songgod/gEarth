#pragma once

#include "oepLayer.h"
#include <osgEarth/Layer>

namespace gEarthPack
{

	public ref class oepUnknownLayer : public oepLayer
	{
	public:
		oepUnknownLayer();

	public:

		property bool Visible
		{
			bool get();
			void set(bool v);
		}

	internal:

		oepUnknownLayer(osgEarth::Layer* layer);
	};
}

