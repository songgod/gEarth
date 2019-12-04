#pragma once
#include "oepRefObject.h"
namespace gEarthPack
{
	public ref class oepResource :
		public oepRefObject<osgEarth::Symbology::Resource>
	{
	public:
		oepResource();
	};
}

