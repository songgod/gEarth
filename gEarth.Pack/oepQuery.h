#pragma once
#include "oepValObject.h"

namespace gEarthPack
{
	public ref class oepQuery :
		public oepValObject<osgEarth::Symbology::Query>
	{
	public:
		oepQuery();
	};
}


