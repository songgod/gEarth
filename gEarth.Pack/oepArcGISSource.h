#pragma once

#include "oepTileSource.h"

namespace gEarthPack
{

	public ref class oepArcGISSource : public oepTileSource
	{
	public:
		oepArcGISSource();

	public:
		property String^ url
		{
			String^ get();
			void set(String^ v);
		}
	};
}

