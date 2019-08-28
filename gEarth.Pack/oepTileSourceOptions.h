#pragma once
#include "oepDriverConfigOptions.h"

namespace gEarthPack
{
	public ref class oepTileSourceOptions : public oepDriverConfigOptions
	{
	public:
		oepTileSourceOptions();

	internal:

		osgEarth::TileSourceOptions* asoeTileSourceOptions();
	};
}
