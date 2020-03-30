#pragma once
#include "oepValObject.h"
namespace gEarthPack
{
	public ref class oepDepthOffsetOptions :
		public oepValObject<osgEarth::DepthOffsetOptions>
	{
	public:
		oepDepthOffsetOptions();

	public:

		property bool Enabled
		{
			bool get();
			void set(bool p);
		}

		property double MinBias
		{
			double get();
			void set(double p);
		}

		property double MaxBias
		{
			double get();
			void set(double p);
		}

		property double MinRange
		{
			double get();
			void set(double p);
		}

		property double MaxRange
		{
			double get();
			void set(double p);
		}

		property bool Automatic
		{
			bool get();
			void set(bool p);
		}
	};
}

