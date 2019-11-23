#pragma once
#include "oepDriverConfigOptions.h"
#include "oepProfileOptions.h"
#include "oepGeoCommon.h"



namespace gEarthPack
{
	public ref class oepFeatureSourceOptions :
		public oepDriverConfigOptions
	{
	public:
		oepFeatureSourceOptions();

	public:

		virtual property String^ Name
		{
			String^ get() override;
			void set(String^ v) override;
		}

		property oepConfigOptionsCollection^ Filters
		{
			oepConfigOptionsCollection^ get();
			void set(oepConfigOptionsCollection^ v);
		}

		property bool OpenWrite
		{
			bool get();
			void set(bool b);
		}

		property oepProfileOptions^ Profile
		{
			oepProfileOptions^ get();
			void set(oepProfileOptions^ p);
		}

		property oepGeoInterpolation GeoInterp
		{
			oepGeoInterpolation get();
			void set(oepGeoInterpolation p);
		}

		property String^ FidAttribute
		{
			String^ get();
			void set(String^ p);
		}


	private:

		oepConfigOptionsCollection^ _filters;
		oepProfileOptions^ _profile;
		oepGeoInterpolation _geoinerp;
	};
}

