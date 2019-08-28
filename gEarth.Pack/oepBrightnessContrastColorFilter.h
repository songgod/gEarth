#pragma once
#include "oepColorFilter.h"
#include "oepVector.h"

namespace gEarthPack
{
	public ref class oepBrightnessContrastColorFilter :
		public oepColorFilter
	{
	public:
		oepBrightnessContrastColorFilter();

	public:

		void Reset() override;

	public:

		property oepVec2f BrightnessContrast
		{
			oepVec2f get();
			void set(oepVec2f v);
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
	};
}

