#pragma once
#include "oepExtension.h"
#include <osgEarthDrivers/sky_simple/SimpleSkyOptions>

namespace gEarthPack
{
	public ref class oepSimpleSkyExtension :
		public oepExtension
	{
	public:
		oepSimpleSkyExtension();

	public:

		property int DataYear
		{
			int get();
			void set(int v);
		}

		property int DataMonth
		{
			int get();
			void set(int v);
		}

		property int DataDay
		{
			int get();
			void set(int v);
		}

		property double DataHours
		{
			double get();
			void set(double v);
		}

		property bool SunVisible
		{
			bool get();
			void set(bool b);
		}

		property bool MoonVisible
		{
			bool get();
			void set(bool b);
		}

		property bool StarsVisible
		{
			bool get();
			void set(bool b);
		}

		property bool AtmosphereVisible
		{
			bool get();
			void set(bool b);
		}

	internal:
		oepSimpleSkyExtension(osgEarth::Extension* ext);
		osgEarth::Util::SkyNode* getoeSkyNode();
		osgEarth::SimpleSky::SimpleSkyOptions* getoeSimpleSkyOptions();
	};
}


