#include "stdafx.h"
#include "oepStringExpression.h"

using namespace gEarthPack;
using namespace osgEarth::Symbology;
using namespace msclr::interop;

oepStringExpression::oepStringExpression()
{
	bind(new StringExpression(), true);
}

String^ oepStringExpression::Infix::get()
{
	return marshal_as<String^>(val()->expr());
}

void oepStringExpression::Infix::set(String^ p)
{
	val()->setInfix(marshal_as<std::string>(p));
	NotifyChanged("Infix");
}

String^ oepStringExpression::Literal::get()
{
	return marshal_as<String^>(val()->eval());
}

void oepStringExpression::Literal::set(String^ p)
{
	val()->setLiteral(marshal_as<std::string>(p));
	NotifyChanged("Literal");
}

bool oepStringExpression::IsEmpty::get()
{
	return val()->empty();
}
