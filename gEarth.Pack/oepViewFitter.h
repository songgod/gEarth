#pragma once

#include "oepViewpoint.h"
#include "Render.h"
#include "oepLayer.h"

namespace gEarthPack
{
	public ref class oepViewFitter
	{
	public:
		static oepViewFitter();

	public:

		static oepViewpoint^ Fitter(oepLayer^ layer, oepMap^ map, Render^ render);
	};
}


