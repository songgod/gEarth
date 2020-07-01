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
	if (ntSymbol())
	{
		ntSymbol()->script() = *(p->val());
		NotifyChanged("Script");
	}
}

void oepSymbol::binded()
{
	_script = gcnew oepStringExpression();
	if (ntSymbol())
		_script->bind(ntSymbol()->script(), false);
}

void oepSymbol::unbinded()
{
	_script->unbind();
}
