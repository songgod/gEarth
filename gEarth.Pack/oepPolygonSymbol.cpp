#include "stdafx.h"
#include "oepPolygonSymbol.h"

using namespace gEarthPack;
using namespace osgEarth::Symbology;

oepPolygonSymbol::oepPolygonSymbol()
{
	bind(new PolygonSymbol());
}

void oepPolygonSymbol::binded()
{
	oepSymbol::binded();
	_fill = gcnew oepFill();
	_fill->bind(as<PolygonSymbol>()->fill());
}

void oepPolygonSymbol::unbinded()
{
	_fill->unbind();
	oepSymbol::unbind();
}

oepFill^ oepPolygonSymbol::Fill::get()
{
	return _fill;
}

void oepPolygonSymbol::Fill::set(oepFill^ p)
{
	PolygonSymbol* to = as<PolygonSymbol>();
	if (to != NULL && p != nullptr)
	{
		to->fill() = *(p->ntFill());
		NotifyChanged("Fill");
	}
}

bool oepPolygonSymbol::OutLine::get()
{
	PolygonSymbol* to = as<PolygonSymbol>();
	if (!to || !to->outline().isSet())
		return false;
	return to->outline().value();
}

void oepPolygonSymbol::OutLine::set(bool p)
{
	PolygonSymbol* to = as<PolygonSymbol>();
	if (!to)
		return;
	to->outline() = p;
	NotifyChanged("OutLine");
}
