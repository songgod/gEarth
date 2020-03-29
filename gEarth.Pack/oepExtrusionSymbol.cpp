#include "stdafx.h"
#include "oepExtrusionSymbol.h"

using namespace gEarthPack;

oepExtrusionSymbol::oepExtrusionSymbol()
{
	bind(new osgEarth::Symbology::ExtrusionSymbol());
}
