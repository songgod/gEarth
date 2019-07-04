#pragma once
#include "oepColorFilter.h"
#include "oepVector.h"
#include <osgEarthUtil/HSLColorFilter>

namespace gEarthPack
{
	public ref class oepHSLColorFilter :
		public oepColorFilter
	{
	public:
		oepHSLColorFilter();

	public:

		void Reset() override;

	public:

		property oepVec3f Offset
		{
			oepVec3f get();
			void set(oepVec3f v);
		}

		property float H
		{
			float get();
			void set(float v);
		}

		property float S
		{
			float get();
			void set(float v);
		}

		property float L
		{
			float get();
			void set(float v);
		}

	internal:

		osgEarth::Util::HSLColorFilter* asoeHSLColorFilter();
	};
}

