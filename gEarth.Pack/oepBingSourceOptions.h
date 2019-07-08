#pragma once
#include "oepTileSourceOptions.h"

namespace gEarthPack
{
	public ref class oepBingSourceOptions : public oepTileSourceOptions
	{
	public:
		oepBingSourceOptions();

	public:

		property String^ apikey
		{
			String^ get();
			void set(String^ v);
		}

		property String^ imagerySet
		{
			String^ get();
			void set(String^ v);
		}

		property String^ imageryMetadataAPI
		{
			String^ get();
			void set(String^ v);
		}
	};
}

