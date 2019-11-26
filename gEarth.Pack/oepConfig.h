#pragma once
#include "oepValObject.h"

namespace gEarthPack
{
	public ref class oepConfig :
		public oepValObject<osgEarth::Config>
	{
	public:
		oepConfig();
	};

}

