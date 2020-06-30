#pragma once
#include "oepValObject.h"

using namespace osgEarth;

namespace gEarthPack
{
	public ref class oepUnits :
		public oepValObject<Units>
	{
	public:
		oepUnits();
		static oepUnits();

	public:

		static property oepUnits^ CENTIMETERS
		{
			oepUnits^ get();
		}

	private:

		static oepUnits^ centimeters;
	};
}


