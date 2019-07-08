#pragma once
#include "oepVisibleLayerOptions.h"
#include "oepTileSourceOptions.h"
#include <osgEarth/TerrainLayer>

namespace gEarthPack
{
	public ref class oepTerrainLayerOptions :
		public oepVisibleLayerOptions
	{
	public:
		oepTerrainLayerOptions();

	public:

		property oepTileSourceOptions^ driver
		{
			oepTileSourceOptions^ get();
			void set(oepTileSourceOptions^ v);
		}

	internal:

		osgEarth::TerrainLayerOptions* asoeTerrainLayerOptions();

	private:

		oepTileSourceOptions^ _driver;
	};
}
