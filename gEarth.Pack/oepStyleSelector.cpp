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
	return Str2Cli(as<osgEarth::Symbology::StyleSelector>()->name());
}

void oepStyleSelector::Name::set(String^ p)
{
	as<osgEarth::Symbology::StyleSelector>()->name() = Str2Std(p);
	NotifyChanged("Name");
}

String^ oepStyleSelector::StyleName::get()
{
	return Str2Cli(as<osgEarth::Symbology::StyleSelector>()->styleName().value());
}

void oepStyleSelector::StyleName::set(String^ p)
{
	as<osgEarth::Symbology::StyleSelector>()->styleName() = Str2Std(p);
	NotifyChanged("StyleName");
}

oepStringExpression^ oepStyleSelector::StyleExpression::get()
{
	return _styleExpression;
}

void oepStyleSelector::StyleExpression::set(oepStringExpression^ p)
{
	StyleSelector* to = as<StyleSelector>();
	if (to != NULL && p != nullptr)
	{
		to->styleExpression() = *(p->as<StringExpression>());
		NotifyChanged("StyleExpression");
	}
}

oepQuery^ oepStyleSelector::Query::get()
{
	return _query;
}

void oepStyleSelector::Query::set(oepQuery^ p)
{
	StyleSelector* to = as<StyleSelector>();
	if (to != NULL && p != nullptr)
	{
		to->query() = *(p->as<osgEarth::Query>());
		NotifyChanged("Query");
	}
}

String^ oepStyleSelector::SelectStyleName::get()
{
	return Str2Cli(as<osgEarth::Symbology::StyleSelector>()->getSelectedStyleName());
}

void oepStyleSelector::binded()
{
	_styleExpression = gcnew oepStringExpression();
	_styleExpression->bind(as<osgEarth::Symbology::StyleSelector>()->styleExpression());

	_query = gcnew oepQuery();
	_query->bind(as<osgEarth::Symbology::StyleSelector>()->query());
}

void oepStyleSelector::unbinded()
{
	_styleExpression->unbind();
	_query->unbind();
}

void gEarthPack::oepStyleSelector::delelehandle()
{
	del<osgEarth::Symbology::StyleSelector>();
}
