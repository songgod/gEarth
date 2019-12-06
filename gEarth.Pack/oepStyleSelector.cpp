#include "stdafx.h"
#include "oepStyleSelector.h"

using namespace gEarthPack;
using namespace osgEarth::Symbology;
using namespace msclr::interop;

oepStyleSelector::oepStyleSelector()
{
	bind(new StyleSelector(), true);
}

String^ oepStyleSelector::Name::get()
{
	return marshal_as<String^>(val()->name());
}

void oepStyleSelector::Name::set(String^ p)
{
	val()->name() = marshal_as<std::string>(p);
	NotifyChanged("Name");
}

String^ oepStyleSelector::StyleName::get()
{
	return marshal_as<String^>(val()->styleName().mutable_value());
}

void oepStyleSelector::StyleName::set(String^ p)
{
	val()->styleName() = marshal_as<std::string>(p);
	NotifyChanged("StyleName");
}

oepStringExpression^ oepStyleSelector::StyleExpression::get()
{
	return _styleExpression;
}

void oepStyleSelector::StyleExpression::set(oepStringExpression^ p)
{
	_styleExpression = p;
	_styleExpression->getVal(val()->styleExpression().mutable_value());
	_styleExpression->bind(&(val()->styleExpression().mutable_value()), false);
}

oepQuery^ oepStyleSelector::Query::get()
{
	return _query;
}

void oepStyleSelector::Query::set(oepQuery^ p)
{
	_query = p;
	_query->getVal(val()->query().mutable_value());
	_query->bind(&(val()->query().mutable_value()), false);
}

String^ oepStyleSelector::SelectStyleName::get()
{
	return marshal_as<String^>(val()->getSelectedStyleName());
}

void oepStyleSelector::binded()
{
	_styleExpression = gcnew oepStringExpression();
	_styleExpression->getVal(val()->styleExpression().mutable_value());
	_styleExpression->bind(&(val()->styleExpression().mutable_value()), false);

	_query = gcnew oepQuery();
	_query->getVal(val()->query().mutable_value());
	_query->bind(&(val()->query().mutable_value()), false);
}

void oepStyleSelector::unbinded()
{
	_styleExpression->unbind();
	_query->unbind();
}
