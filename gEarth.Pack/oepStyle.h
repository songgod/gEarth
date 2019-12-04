#pragma once
#include "oepValObject.h"
#include "oepValMap.h"

namespace gEarthPack
{
	public ref class oepStyle :
		public oepValObject<osgEarth::Symbology::Style>
	{
	public:
		oepStyle();
	};

	public ref class oepStyleMap : oepValMap<oepStyle, osgEarth::Symbology::Style>
	{

	};
}


