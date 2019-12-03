#pragma once
#include "oepRefObject.h"
namespace gEarthPack
{
	public ref class oepSymbol :
		public oepRefObject<osgEarth::Symbology::Symbol>
	{
	public:
		oepSymbol();
	};
}

