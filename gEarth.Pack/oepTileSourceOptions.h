#pragma once
#include "oepDriverConfigOptions.h"
#include <osgEarth/TileSource>

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
