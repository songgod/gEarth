#pragma once
#include "oepVisibleLayerOptions.h"
#include "oepFeatureSourceOptions.h"

namespace gEarthPack
{
	public ref class oepFeatureModelLayerOptions :
		public oepVisibleLayerOptions
	{
	public:
		oepFeatureModelLayerOptions();

	public:

		property oepFeatureSourceOptions^ driver
		{
			oepFeatureSourceOptions^ get();
			void set(oepFeatureSourceOptions^ v);
		}

	private:

		oepFeatureSourceOptions^ _driver;
	};
}

