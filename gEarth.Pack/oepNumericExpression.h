#pragma once
#include "oepValObject.h"
namespace gEarthPack
{
	public ref class oepNumericExpression :
		public oepValObject
	{
	public:
		oepNumericExpression();

	internal:

		virtual void delelehandle() override;

	internal:

		osgEarth::NumericExpression* ntNumericExpression() { return as<osgEarth::NumericExpression>(); }
	};
}

