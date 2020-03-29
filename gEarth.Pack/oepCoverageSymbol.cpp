#include "stdafx.h"
#include "oepCoverageSymbol.h"

using namespace gEarthPack;

oepCoverageSymbol::oepCoverageSymbol()
{
	bind(new osgEarth::Symbology::CoverageSymbol());
}
