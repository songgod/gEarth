#include "stdafx.h"
#include "oepStringExpression.h"

using namespace gEarthPack;
using namespace osgEarth::Symbology;


oepStringExpression::oepStringExpression()
{
	bind(new StringExpression(), true);
}

void gEarthPack::oepStringExpression::delelehandle()
{
	del<osgEarth::Symbology::StringExpression>();
}

String^ oepStringExpression::Infix::get()
{
	return Str2Cli(as<StringExpression>()->expr());
}

void oepStringExpression::Infix::set(String^ p)
{
	as<StringExpression>()->setInfix(Str2Std(p));
	NotifyChanged("Infix");
}

String^ oepStringExpression::Literal::get()
{
	return Str2Cli(as<StringExpression>()->eval());
}

void oepStringExpression::Literal::set(String^ p)
{
	as<StringExpression>()->setLiteral(Str2Std(p));
	NotifyChanged("Literal");
}

bool oepStringExpression::IsEmpty::get()
{
	return as<StringExpression>()->empty();
}
