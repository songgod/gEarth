#pragma once

#include "oepTileSourceOptions.h"

namespace gEarthPack
{

	public ref class oepArcGISSourceOptions : public oepTileSourceOptions
	{
	public:
		oepArcGISSourceOptions();

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

