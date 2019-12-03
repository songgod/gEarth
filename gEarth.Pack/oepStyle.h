#pragma once
#include "oepValObject.h"

namespace gEarthPack
{
	public ref class oepStyle :
		public oepValObject<osgEarth::Symbology::Style>
	{
	public:
		oepStyle();
	};
}


