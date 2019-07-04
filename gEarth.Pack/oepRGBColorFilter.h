#pragma once
#include "oepColorFilter.h"
#include "oepVector.h"
#include <osgEarthUtil/RGBColorFilter>

namespace gEarthPack
{
	public ref class oepRGBColorFilter :
		public oepColorFilter
	{
	public:
		oepRGBColorFilter();

	public:

		void Reset() override;

	public:

		property oepVec3f Offset
		{
			oepVec3f get();
			void set(oepVec3f v);
		}

		property float R
		{
			float get();
			void set(float v);
		}

		property float G
		{
			float get();
			void set(float v);
		}

		property float B
		{
			float get();
			void set(float v);
		}

	internal:

		osgEarth::Util::RGBColorFilter* asoeRGBColorFilter();
	};
}
