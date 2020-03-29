#include "stdafx.h"
#include "oepPointSymbol.h"

using namespace gEarthPack;

oepPointSymbol::oepPointSymbol()
{
	bind(new osgEarth::Symbology::PointSymbol());
}
