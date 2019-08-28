#pragma once
#include "oepColorFilter.h"
#include "oepVector.h"

namespace gEarthPack
{
	public ref class oepChromaKeyColorFilter :
		public oepColorFilter
	{
	public:
		oepChromaKeyColorFilter();

	public:

		void Reset() override;

	public:

		property oepVec3f Color
		{
			oepVec3f get();
			void set(oepVec3f v);
		}

		property float Distance
		{
			float get();
			void set(float v);
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

		osgEarth::Util::ChromaKeyColorFilter* asoeChromaKeyColorFilter();
	};
}

