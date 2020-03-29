#include "stdafx.h"
#include "oepBBoxSymbol.h"

using namespace gEarthPack;

oepBBoxSymbol::oepBBoxSymbol()
{
	bind(new osgEarth::Symbology::BBoxSymbol());
}
