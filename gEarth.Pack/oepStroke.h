#pragma once
#include "oepValObject.h"
#include "oepVector.h"

namespace gEarthPack
{
	public ref class oepStroke :
		public oepValObject<osgEarth::Symbology::Stroke>
	{
	public:
		oepStroke();

	public:

		enum class oepLineCapStyle
		{
			Flat,
			Square,
			Round
		};

		enum class oepLineJoinStyle
		{
			Mitre,
			Round
		};

	public:

		property oepVec4f Color
		{
			oepVec4f get();
			void set(oepVec4f p);
		}

		property oepLineCapStyle LineCap
		{
			oepLineCapStyle get();
			void set(oepLineCapStyle p);
		}

		property oepLineJoinStyle LineJoin
		{
			oepLineJoinStyle get();
			void set(oepLineJoinStyle p);
		}

		property float Width
		{
			float get();
			void set(float p);
		}

	};
}

