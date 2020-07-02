#pragma once
#include "oepValObject.h"

using namespace osgEarth;

namespace gEarthPack
{
	public ref class oepUnits :
		public oepValObject
	{
	public:
		oepUnits();
		static oepUnits();

	public:

		static property oepUnits^ CENTIMETERS
		{
			oepUnits^ get();
		}

	internal:

		virtual void delelehandle() override;

	private:

		static oepUnits^ centimeters;
	};
}


