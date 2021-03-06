#pragma once


#include "oepRender.h"
#include "oepMap.h"
#include "oepViewpoint.h"
#include "oepLayer.h"

namespace gEarthPack
{
	public ref class oepViewFitter
	{
	public:
		static oepViewFitter();

	public:

		static oepViewpoint^ Fitter(oepLayer^ layer, oepMap^ map, oepRender^ render);
	};
}


