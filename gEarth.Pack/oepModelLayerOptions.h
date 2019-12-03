#pragma once
#include "oepVisibleLayerOptions.h"
#include "oepModelSourceOptions.h"

namespace gEarthPack
{
	public ref class oepModelLayerOptions :
		public oepVisibleLayerOptions
	{
	public:
		oepModelLayerOptions();

	public:

		property oepModelSourceOptions^ driver
		{
			oepModelSourceOptions^ get();
			void set(oepModelSourceOptions^ v);
		}

	internal:

		virtual void binded() override;
		virtual void unbinded() override;

	private:

		oepModelSourceOptions^ _driver;
	};
}

