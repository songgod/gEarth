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

	internal:

		virtual void binded() override;
		virtual void unbinded() override;

	private:

		oepFeatureSourceOptions^ _driver;
	};
}

