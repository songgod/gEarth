#include "stdafx.h"
#include "oepStyleSelector.h"

using namespace gEarthPack;
using namespace osgEarth::Symbology;


oepStyleSelector::oepStyleSelector()
{
	bind(new StyleSelector(), true);
}

String^ oepStyleSelector::Name::get()
{
	return Str2Cli(val()->name());
}

void oepStyleSelector::Name::set(String^ p)
{
	val()->name() = Str2Std(p);
	NotifyChanged("Name");
}

String^ oepStyleSelector::StyleName::get()
{
	return Str2Cli(val()->styleName().value());
}

void oepStyleSelector::StyleName::set(String^ p)
{
	val()->styleName() = Str2Std(p);
	NotifyChanged("StyleName");
}

oepStringExpression^ oepStyleSelector::StyleExpression::get()
{
	return _styleExpression;
}

void oepStyleSelector::StyleExpression::set(oepStringExpression^ p)
{
	_styleExpression = p;
	StyleSelector* to = as<StyleSelector>();
	if (to != NULL && _query != nullptr)
	{
		to->styleExpression() = *(_query->as<StringExpression>());
	}
}

oepQuery^ oepStyleSelector::Query::get()
{
	return _query;
}

void oepStyleSelector::Query::set(oepQuery^ p)
{
	_query = p;
	StyleSelector* to = as<StyleSelector>();
	if (to != NULL && _query != nullptr)
	{
		to->query() = *(_query->as<osgEarth::Query>());
	}
}

String^ oepStyleSelector::SelectStyleName::get()
{
	return Str2Cli(val()->getSelectedStyleName());
}

void oepStyleSelector::binded()
{
	_styleExpression = gcnew oepStringExpression();
	_styleExpression->bind(val()->styleExpression(), false);

	_query = gcnew oepQuery();
	_query->bind(val()->query(), false);
}

void oepStyleSelector::unbinded()
{
	_styleExpression->unbind();
	_query->unbind();
}
