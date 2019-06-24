#pragma once

#include "oepTileSource.h"
namespace gEarthPack
{
	public ref class oepGDALSource : public oepTileSource
	{
	public:
		oepGDALSource();

	public:
		
		property String^ url
		{
			String^ get();
			void set(String^ v);
		}
	};
}
