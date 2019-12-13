#include "stdafx.h"
#include "oepStringExpression.h"

using namespace gEarthPack;
using namespace osgEarth::Symbology;


oepStringExpression::oepStringExpression()
{
	bind(new StringExpression(), true);
}

String^ oepStringExpression::Infix::get()
{
	return Str2Cli(val()->expr());
}

void oepStringExpression::Infix::set(String^ p)
{
	val()->setInfix(Str2Std(p));
	NotifyChanged("Infix");
}

String^ oepStringExpression::Literal::get()
{
	return Str2Cli(val()->eval());
}

void oepStringExpression::Literal::set(String^ p)
{
	val()->setLiteral(Str2Std(p));
	NotifyChanged("Literal");
}

bool oepStringExpression::IsEmpty::get()
{
	return val()->empty();
}
