#pragma once
#include "oepConfigOptions.h"
#include "oepBounds.h"

namespace gEarthPack
{
	public ref class oepProfileOptions :
		public oepConfigOptions
	{
	public:
		oepProfileOptions();

	public:

		property String^ NamedProfile
		{
			String^ get();
			void set(String^ v);
		}

		property String^ SrsString
		{
			String^ get();
			void set(String^ v);
		}

		property String^ VsrsString
		{
			String^ get();
			void set(String^ v);
		}

		property oepBounds^ Bounds
		{
			oepBounds^ get();
			void set(oepBounds^ p);
		}

		property int NumTilesWideAtLod0
		{
			int get();
			void set(int p);
		}

		property int NumTilesHighAtLod0
		{
			int get();
			void set(int p);
		}

	private:

		oepBounds^ _bounds;
	};
}


