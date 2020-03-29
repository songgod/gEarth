#include "stdafx.h"
#include "oepRenderSymbol.h"

using namespace gEarthPack;

oepRenderSymbol::oepRenderSymbol()
{
	bind(new osgEarth::Symbology::RenderSymbol());
}
