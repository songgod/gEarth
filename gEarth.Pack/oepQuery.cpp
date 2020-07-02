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
	_bounds->bind(ntQuery()->bounds());
}

void gEarthPack::oepQuery::unbinded()
{
	_bounds->unbind();
}

void gEarthPack::oepQuery::delelehandle()
{
	del<osgEarth::Symbology::Query>();
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
	return Str2Cli(ntQuery()->expression().value());
}

void oepQuery::Expression::set(String^ p)
{
	ntQuery()->expression() = Str2Std(p);
	NotifyChanged("Expression");
}

String^ oepQuery::OrderBy::get()
{
	return Str2Cli(ntQuery()->orderby().value());
}

void oepQuery::OrderBy::set(String^ p)
{
	ntQuery()->orderby() = Str2Std(p);
	NotifyChanged("OrderBy");
}

int oepQuery::Limit::get()
{
	return ntQuery()->limit().value();
}

void oepQuery::Limit::set(int p)
{
	ntQuery()->limit() = p;
	NotifyChanged("Limit");
}
