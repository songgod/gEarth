#pragma once
#include "oepLayer.h"
#include "oepVisibleLayerOptions.h"

namespace osgEarth
{
	class VisibleLayer;
}

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
	};
}

