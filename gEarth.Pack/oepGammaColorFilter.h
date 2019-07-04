#pragma once
#include "oepColorFilter.h"
#include "oepVector.h"
#include <osgEarthUtil/GammaColorFilter>

namespace gEarthPack
{
	public ref class oepGammaColorFilter :
		public oepColorFilter
	{
	public:
		oepGammaColorFilter();

	public:

		property oepVec3f Gamma
		{
			oepVec3f get();
			void set(oepVec3f v);
		}

		property float V0
		{
			float get();
			void set(float v);
		}

		property float V1
		{
			float get();
			void set(float v);
		}

		property float V2
		{
			float get();
			void set(float v);
		}

	internal:

		osgEarth::Util::GammaColorFilter* asoGammaColorFilter();
	};
}

