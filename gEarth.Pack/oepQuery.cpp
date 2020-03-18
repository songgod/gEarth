#include "stdafx.h"
#include "oepQuery.h"

using namespace gEarthPack;


oepQuery::oepQuery()
{
	bind(new osgEarth::Symbology::Query(),true);
}

void gEarthPack::oepQuery::binded()
{
	_bounds = gcnew oepBounds();
	_bounds->bind(val()->bounds(), false);
}

void gEarthPack::oepQuery::unbinded()
{
	_bounds->unbind();
}

oepBounds^ oepQuery::Bounds::get()
{
	return _bounds;
}

void oepQuery::Bounds::set(oepBounds^ p)
{
	osgEarth::Query* to = as<osgEarth::Query>();
	if (to != NULL && p != nullptr)
	{
		to->bounds() = *(p->as<osgEarth::Bounds>());
		NotifyChanged("Bounds");
	}
}

String^ oepQuery::Expression::get()
{
	return Str2Cli(val()->expression().value());
}

void oepQuery::Expression::set(String^ p)
{
	val()->expression() = Str2Std(p);
	NotifyChanged("Expression");
}

String^ oepQuery::OrderBy::get()
{
	return Str2Cli(val()->orderby().value());
}

void oepQuery::OrderBy::set(String^ p)
{
	val()->orderby() = Str2Std(p);
	NotifyChanged("OrderBy");
}

int oepQuery::Limit::get()
{
	return val()->limit().value();
}

void oepQuery::Limit::set(int p)
{
	val()->limit() = p;
	NotifyChanged("Limit");
}
