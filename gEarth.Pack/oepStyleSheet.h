#pragma once
#include "oepRefObject.h"

namespace gEarthPack
{
	public ref class oepStyleSheet :
		public oepRefObject<osgEarth::Symbology::StyleSheet>
	{
	public:
		oepStyleSheet();
	};
}


