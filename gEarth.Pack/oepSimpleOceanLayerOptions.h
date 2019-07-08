#pragma once
#include "oepVisibleLayerOptions.h"
#include <osgEarthUtil/SimpleOceanLayer>
#include "oepVector.h"

namespace gEarthPack
{
	public ref class oepSimpleOceanLayerOptions :
		public oepVisibleLayerOptions
	{
	public:
		oepSimpleOceanLayerOptions();

	public:

		property oepVec4f Color
		{
			oepVec4f get();
			void set(oepVec4f v);
		}

		property float MaxAltitude
		{
			float get();
			void set(float v);
		}

		property String^ MaskLayer
		{
			String^ get();
			void set(String^ v);
		}

		property bool UseBathymetry
		{
			bool get();
			void set(bool b);
		}

		property String^ TextureUrl
		{
			String^ get();
			void set(String^ url);
		}

		property unsigned TextureLOD
		{
			unsigned get();
			void set(unsigned v);
		}

	internal:

		osgEarth::Util::SimpleOceanLayerOptions* asoeSimpleOceanLayerOptions();
	};
}
