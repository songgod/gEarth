#pragma once
#include "oepValObject.h"
namespace gEarthPack
{
	public ref class oepFadeOptions :
		public oepValObject
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

	internal:

		virtual void delelehandle() override;

	internal:

		osgEarth::FadeOptions* ntFadeOptions() { return as<osgEarth::FadeOptions>(); }
	};
}

