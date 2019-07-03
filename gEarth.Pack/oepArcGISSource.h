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

		property String^ token
		{
			String^ get();
			void set(String^ v);
		}

		property String^ format
		{
			String^ get();
			void set(String^ v);
		}

		property String^ layers
		{
			String^ get();
			void set(String^ v);
		}
	};
}

