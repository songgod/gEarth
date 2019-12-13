#pragma once
#include "oepValObject.h"
namespace gEarthPack
{
	public ref class oepFadeOptions :
		public oepValObject<osgEarth::FadeOptions>
	{
	public:
		oepFadeOptions();

	public:

		property float Duration
		{
			float get();
			void set(float p);
		}

		property float MaxRange
		{
			float get();
			void set(float p);
		}

		property float AttenuationDistance
		{
			float get();
			void set(float p);
		}
	};
}

