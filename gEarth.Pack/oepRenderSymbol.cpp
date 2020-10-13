#include "stdafx.h"
#include "oepRenderSymbol.h"

using namespace gEarthPack;
using namespace osgEarth::Symbology;

oepRenderSymbol::oepRenderSymbol()
{
	bind(new RenderSymbol());
}

void oepRenderSymbol::binded()
{
	oepSymbol::binded();
	_depthoffset = gcnew oepDepthOffsetOptions();
	_depthoffset->bind(as<RenderSymbol>()->depthOffset());
	_order = gcnew oepNumericExpression();
	_order->bind(as<RenderSymbol>()->order());
}

void oepRenderSymbol::unbinded()
{
	_depthoffset->unbind();
	_order->unbind();
	oepSymbol::unbinded();
}

bool oepRenderSymbol::DepthTest::get()
{
	if (as<RenderSymbol>()->depthTest().isSet())
		return 0.0f;
	return as<RenderSymbol>()->depthTest().value();
}

void oepRenderSymbol::DepthTest::set(bool p)
{
	as<RenderSymbol>()->depthTest() = p;
	NotifyChanged("DepthTest");
}

bool oepRenderSymbol::Lighting::get()
{
	if (as<RenderSymbol>()->lighting().isSet())
		return 0.0f;
	return as<RenderSymbol>()->lighting().value();
}

void oepRenderSymbol::Lighting::set(bool p)
{
	as<RenderSymbol>()->lighting() = p;
	NotifyChanged("Lighting");
}

bool oepRenderSymbol::BackfaceCulling::get()
{
	if (as<RenderSymbol>()->backfaceCulling().isSet())
		return 0.0f;
	return as<RenderSymbol>()->backfaceCulling().value();
}

void oepRenderSymbol::BackfaceCulling::set(bool p)
{
	as<RenderSymbol>()->backfaceCulling() = p;
	NotifyChanged("BackfaceCulling");
}

oepNumericExpression^ oepRenderSymbol::Order::get()
{
	return _order;
}

void oepRenderSymbol::Order::set(oepNumericExpression^ p)
{
	as<RenderSymbol>()->order() = *(p->as<osgEarth::NumericExpression>());
	NotifyChanged("Order");
}

unsigned int oepRenderSymbol::ClipPlane::get()
{
	if (as<RenderSymbol>()->clipPlane().isSet())
		return 0.0f;
	return as<RenderSymbol>()->clipPlane().value();
}

void oepRenderSymbol::ClipPlane::set(unsigned int p)
{
	as<RenderSymbol>()->clipPlane() = p;
	NotifyChanged("ClipPlane");
}

float oepRenderSymbol::MinAlpha::get()
{
	if (as<RenderSymbol>()->minAlpha().isSet())
		return 0.0f;
	return as<RenderSymbol>()->minAlpha().value();
}

void oepRenderSymbol::MinAlpha::set(float p)
{
	as<RenderSymbol>()->minAlpha() = p;
	NotifyChanged("MinAlpha");
}

bool oepRenderSymbol::Transparent::get()
{
	if (as<RenderSymbol>()->transparent().isSet())
		return 0.0f;
	return as<RenderSymbol>()->transparent().value();
}

void oepRenderSymbol::Transparent::set(bool p)
{
	as<RenderSymbol>()->transparent() = p;
	NotifyChanged("Transparent");
}

String^ oepRenderSymbol::RenderBin::get()
{
	if (as<RenderSymbol>()->renderBin().isSet())
		return "";
	return Str2Cli(as<RenderSymbol>()->renderBin().value());
}

void oepRenderSymbol::RenderBin::set(String^ p)
{
	as<RenderSymbol>()->renderBin() = Str2Std(p);
	NotifyChanged("RenderBin");
}

bool oepRenderSymbol::Decal::get()
{
	if (as<RenderSymbol>()->decal().isSet())
		return 0.0f;
	return as<RenderSymbol>()->decal().value();
}

void oepRenderSymbol::Decal::set(bool p)
{
	as<RenderSymbol>()->decal() = p;
	NotifyChanged("Decal");
}

double oepRenderSymbol::MaxCreaseAngle::get()
{
	if (as<RenderSymbol>()->maxCreaseAngle().isSet())
		return 0.0f;
	return as<RenderSymbol>()->maxCreaseAngle().value().getValue();
}

void oepRenderSymbol::MaxCreaseAngle::set(double p)
{
	as<RenderSymbol>()->maxCreaseAngle() = p;
	NotifyChanged("MaxCreaseAngle");
}

double oepRenderSymbol::MaxAltitude::get()
{
	if (as<RenderSymbol>()->maxAltitude().isSet())
		return 0.0;
	return as<RenderSymbol>()->maxAltitude().value().getValue();
}

void oepRenderSymbol::MaxAltitude::set(double p)
{
	as<RenderSymbol>()->maxAltitude() = p;
	NotifyChanged("MaxAltitude");
}

oepDepthOffsetOptions^ oepRenderSymbol::DepthOffset::get()
{
	return _depthoffset;
}

void oepRenderSymbol::DepthOffset::set(oepDepthOffsetOptions^ p)
{
	as<RenderSymbol>()->depthOffset() = *(p->as<osgEarth::DepthOffsetOptions>());
	NotifyChanged("DepthOffset");
}
