#pragma once

#include "oepTileSourceOptions.h"
namespace gEarthPack
{
	public ref class oepGDALSourceOptions : public oepTileSourceOptions
	{
	public:
		oepGDALSourceOptions();

	public:
		
		property String^ url
		{
			String^ get();
			void set(String^ v);
		}
	};
}
