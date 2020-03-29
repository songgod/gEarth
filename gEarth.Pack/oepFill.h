#pragma once
#include "oepValObject.h"
#include "oepVector.h"

namespace gEarthPack
{
	public ref class oepFill :
		public oepValObject<osgEarth::Symbology::Fill>
	{
	public:
		oepFill();

	public:

		property oepVec4f Color
		{
			oepVec4f get();
			void set(oepVec4f p);
		}
	};
}

