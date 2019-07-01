#pragma once
#include "oepTileSource.h"

namespace gEarthPack
{
	public ref class oepBingSource : public oepTileSource
	{
	public:
		oepBingSource();

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

