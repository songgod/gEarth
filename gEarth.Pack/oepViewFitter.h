#pragma once

namespace gEarthPack
{
	ref class Render;
	ref class oepMap;
	ref class oepLayer;
	ref class oepViewpoint;
	public ref class oepViewFitter
	{
	public:
		static oepViewFitter();

	public:

		static oepViewpoint^ Fitter(oepLayer^ layer, oepMap^ map, Render^ render);
	};
}


