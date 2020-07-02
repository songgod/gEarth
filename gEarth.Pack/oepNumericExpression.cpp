#include "stdafx.h"
#include "oepNumericExpression.h"

using namespace gEarthPack;

oepNumericExpression::oepNumericExpression()
{
	bind(new osgEarth::Symbology::NumericExpression(), true);
}

void gEarthPack::oepNumericExpression::delelehandle()
{
	del<osgEarth::Symbology::NumericExpression>();
}
