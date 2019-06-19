#pragma once
#include "oepVisibleLayer.h"
#include "oepTileSource.h"
#include <osgEarth/TerrainLayer>

namespace gEarthPack
{
	public ref class oepTerrainLayer : public oepVisibleLayer
	{
	public:
		oepTerrainLayer(oepTileSource^ source);

	public:

		property oepTileSource^ TileSource
		{
			oepTileSource^ get()
			{
				return _source;
			}
		}

	public:

		osgEarth::TerrainLayer* asoeTerrainLayer();

	protected:

		oepTerrainLayer(){}

	protected:

		oepTileSource^ _source;
	};
}

