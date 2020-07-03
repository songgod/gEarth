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
	if (as<osgEarth::Symbol>())
	{
		as<osgEarth::Symbol>()->script() = *(p->as<StringExpression>());
		NotifyChanged("Script");
	}
}

void oepSymbol::binded()
{
	_script = gcnew oepStringExpression();
	if (as<osgEarth::Symbol>())
		_script->bind(as<osgEarth::Symbol>()->script());
}

void oepSymbol::unbinded()
{
	_script->unbind();
}
