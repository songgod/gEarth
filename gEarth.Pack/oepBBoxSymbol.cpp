#include "stdafx.h"
#include "oepBBoxSymbol.h"

using namespace gEarthPack;
using namespace osgEarth::Symbology;

oepBBoxSymbol::oepBBoxSymbol()
{
	bind(new BBoxSymbol());
}

oepFill^ oepBBoxSymbol::Fill::get()
{
	return _fill;
}

void oepBBoxSymbol::Fill::set(oepFill^ p)
{
	_fill = p;
	NotifyChanged("Fill");
}
