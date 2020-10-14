#include "stdafx.h"
#include "oepLineSymbol.h"

using namespace gEarthPack;
using namespace osgEarth::Symbology;

oepLineSymbol::oepLineSymbol()
{
	bind(new LineSymbol());
}

void gEarthPack::oepLineSymbol::binded()
{
	oepSymbol::binded();
	_stroke = gcnew oepStroke();
	_stroke->bind(as<LineSymbol>()->stroke());
	_imageurl = gcnew oepStringExpression();
	_imageurl->bind(as<LineSymbol>()->imageURI());
}

void gEarthPack::oepLineSymbol::unbinded()
{
	_stroke->unbind();
	_imageurl->unbind();
	oepSymbol::unbinded();
}

gEarthPack::oepStroke^ gEarthPack::oepLineSymbol::Stroke::get()
{
	return _stroke;
}

void gEarthPack::oepLineSymbol::Stroke::set(oepStroke^ p)
{
	LineSymbol* ls = as<LineSymbol>();
	if (ls != NULL && p != nullptr)
	{
		ls->stroke() = *(p->as<osgEarth::Symbology::Stroke>());
		NotifyChanged("Stroke");
	}
}

double gEarthPack::oepLineSymbol::TessellationSize::get()
{
	return as<LineSymbol>()->tessellationSize()->getValue();
}

void gEarthPack::oepLineSymbol::TessellationSize::set(double p)
{
	as<LineSymbol>()->tessellationSize() = p;
	NotifyChanged("TessellationSize");
}

unsigned int gEarthPack::oepLineSymbol::Tessellation::get()
{
	return as<LineSymbol>()->tessellation().value();
}

void gEarthPack::oepLineSymbol::Tessellation::set(unsigned int p)
{
	as<LineSymbol>()->tessellation() = p;
	NotifyChanged("Tessellation");
}

float gEarthPack::oepLineSymbol::CreaseAngle::get()
{
	return as<LineSymbol>()->creaseAngle().value();
}

void gEarthPack::oepLineSymbol::CreaseAngle::set(float p)
{
	as<LineSymbol>()->creaseAngle() = p;
	NotifyChanged("CreaseAngle");
}

gEarthPack::oepStringExpression^ gEarthPack::oepLineSymbol::ImageURI::get()
{
	return _imageurl;
}

void gEarthPack::oepLineSymbol::ImageURI::set(oepStringExpression^ p)
{
	LineSymbol* ls = as<LineSymbol>();
	if (ls != NULL && p != nullptr)
	{
		ls->imageURI() = *(p->as<osgEarth::StringExpression>());
		NotifyChanged("ImageURI");
	}
}
