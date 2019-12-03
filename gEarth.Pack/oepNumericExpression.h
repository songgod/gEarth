#pragma once
#include "oepValObject.h"
namespace gEarthPack
{
	public ref class oepNumericExpression :
		public oepValObject<osgEarth::Symbology::NumericExpression>
	{
	public:
		oepNumericExpression();
	};
}

