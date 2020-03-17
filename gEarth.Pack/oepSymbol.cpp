#include "stdafx.h"
#include "oepSymbol.h"

using namespace gEarthPack;
using namespace osgEarth::Symbology;

oepSymbol::oepSymbol()
{
	
}

oepStringExpression^ oepSymbol::Script::get()
{
	return _script;
}

void oepSymbol::Script::set(oepStringExpression^ p)
{
	_script = p;
	if (ref())
		_script->bind(ref()->script(), false);
}

void oepSymbol::binded()
{
	_script = gcnew oepStringExpression();
	if (ref())
		_script->bind(ref()->script(), false);
}

void oepSymbol::unbinded()
{
	_script->unbind();
}
