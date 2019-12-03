#include "stdafx.h"
#include "oepQuery.h"

using namespace gEarthPack;
using namespace msclr::interop;

oepQuery::oepQuery()
{
	bind(new osgEarth::Symbology::Query(),true);
}

void gEarthPack::oepQuery::binded()
{
	_bounds = gcnew oepBounds();
	_bounds->bind(&(val()->bounds().mutable_value()), false);
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
	_bounds = p;
	if (p != nullptr)
	{
		p->getVal(val()->bounds().mutable_value());
		p->bind(&(val()->bounds().mutable_value()),false);
	}
	NotifyChanged("Bounds");
}

String^ oepQuery::Expression::get()
{
	return marshal_as<String^>(val()->expression().value());
}

void oepQuery::Expression::set(String^ p)
{
	val()->expression() = marshal_as<std::string>(p);
	NotifyChanged("Expression");
}

String^ oepQuery::OrderBy::get()
{
	return marshal_as<String^>(val()->orderby().value());
}

void oepQuery::OrderBy::set(String^ p)
{
	val()->orderby() = marshal_as<std::string>(p);
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
