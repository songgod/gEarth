#pragma once
#include "oepVisibleLayerOptions.h"
#include "oepTileSourceOptions.h"

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

	private:

		oepTileSourceOptions^ _driver;
	};
}
