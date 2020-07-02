#include "stdafx.h"
#include "oepStroke.h"

using namespace gEarthPack;
using namespace osgEarth::Symbology;

oepStroke::oepStroke()
{
	bind(new Stroke(),true);
}

void gEarthPack::oepStroke::delelehandle()
{
	del<osgEarth::Symbology::Stroke>();
}

oepVec4f oepStroke::Color::get()
{
	return oepVec4f(ntStroke()->color());
}

void oepStroke::Color::set(oepVec4f p)
{
	ntStroke()->color() = p.as();
	NotifyChanged("Color");
}

oepStroke::oepLineCapStyle oepStroke::LineCap::get()
{
	Stroke::LineCapStyle lc = ntStroke()->lineCap().value();
	switch (lc)
	{
	case osgEarth::Symbology::Stroke::LINECAP_FLAT:
		return oepStroke::oepLineCapStyle::Flat;
	case osgEarth::Symbology::Stroke::LINECAP_SQUARE:
		return oepStroke::oepLineCapStyle::Square;
	case osgEarth::Symbology::Stroke::LINECAP_ROUND:
		return oepStroke::oepLineCapStyle::Round;
	default:
		break;
	}
	return oepStroke::oepLineCapStyle::Flat;
}

void oepStroke::LineCap::set(oepLineCapStyle p)
{
	switch (p)
	{
	case oepStroke::oepLineCapStyle::Flat:
		ntStroke()->lineCap() = osgEarth::Symbology::Stroke::LINECAP_FLAT;
		break;
	case oepStroke::oepLineCapStyle::Square:
		ntStroke()->lineCap() = osgEarth::Symbology::Stroke::LINECAP_SQUARE;
		break;
	case oepStroke::oepLineCapStyle::Round:
		ntStroke()->lineCap() = osgEarth::Symbology::Stroke::LINECAP_ROUND;
		break;
	default:
		break;
	}
	NotifyChanged("LineCap");
}

oepStroke::oepLineJoinStyle oepStroke::LineJoin::get()
{
	Stroke::LineJoinStyle lj = ntStroke()->lineJoin().value();
	switch (lj)
	{
	case osgEarth::Symbology::Stroke::LINEJOIN_MITRE:
		return oepStroke::oepLineJoinStyle::Mitre;
	case osgEarth::Symbology::Stroke::LINEJOIN_ROUND:
		return oepStroke::oepLineJoinStyle::Round;
	default:
		break;
	}
	return oepStroke::oepLineJoinStyle::Mitre;
}

void oepStroke::LineJoin::set(oepLineJoinStyle p)
{
	switch (p)
	{
	case oepStroke::oepLineJoinStyle::Mitre:
		ntStroke()->lineJoin() = osgEarth::Symbology::Stroke::LINEJOIN_MITRE;
		break;
	case oepStroke::oepLineJoinStyle::Round:
		ntStroke()->lineJoin() = osgEarth::Symbology::Stroke::LINEJOIN_ROUND;
		break;
	default:
		break;
	}
	NotifyChanged("LineJoin");
}

float oepStroke::Width::get()
{
	return ntStroke()->width().value();
}

void oepStroke::Width::set(float p)
{
	ntStroke()->width() = p;
	NotifyChanged("Width");
}


