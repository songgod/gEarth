#pragma once
#include "oepColorFilter.h"
#include "oepVector.h"
#include <osgEarthUtil/CMYKColorFilter>

namespace gEarthPack
{
	public ref class oepCMYKColorFilter :
		public oepColorFilter
	{
	public:
		oepCMYKColorFilter();

	public:

		void Reset() override;

	public:

		property oepVec4f Offset
		{
			oepVec4f get();
			void set(oepVec4f v);
		}

		property float C
		{
			float get();
			void set(float v);
		}

		property float M
		{
			float get();
			void set(float v);
		}

		property float Y
		{
			float get();
			void set(float v);
		}

		property float K
		{
			float get();
			void set(float v);
		}

	internal:

		osgEarth::Util::CMYKColorFilter* asoCMYKColorFilter();
	};
}
