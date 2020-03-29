#include "stdafx.h"
#include "oepLineSymbol.h"

using namespace gEarthPack;

oepLineSymbol::oepLineSymbol()
{
	bind(new osgEarth::Symbology::LineSymbol());
}
