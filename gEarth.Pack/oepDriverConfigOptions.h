#pragma once

#include "oepConfigOptions.h"

namespace gEarthPack
{
	public ref class oepDriverConfigOptions : oepConfigOptions
	{
	public:
		oepDriverConfigOptions();

	public:

		property String^ Driver
		{
			String^ get();
			void set(String^ p);
		}
	};

}

