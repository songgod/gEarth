#include "stdafx.h"
#include "oepTextSymbol.h"

using namespace gEarthPack;

oepTextSymbol::oepTextSymbol()
{
	bind(new osgEarth::Symbology::TextSymbol());
}
