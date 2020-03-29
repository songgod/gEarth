#include "stdafx.h"
#include "oepAltitudeSymbol.h"

using namespace gEarthPack;
using namespace osgEarth::Symbology;

oepAltitudeSymbol::oepAltitudeSymbol()
{
	bind(new AltitudeSymbol());
}


void oepAltitudeSymbol::binded()
{
	oepSymbol::binded();
	_verticalOffset = gcnew oepNumericExpression();
	_verticalOffset->bind(as<AltitudeSymbol>()->verticalOffset(), false);
	_verticalScale = gcnew oepNumericExpression();
	_verticalScale->bind(as<AltitudeSymbol>()->verticalScale(), false);
}

void oepAltitudeSymbol::unbinded()
{
	_verticalOffset->unbind();
	_verticalScale->unbind();
	oepSymbol::unbind();
}

oepAltitudeSymbol::oepClamping oepAltitudeSymbol::Clamping::get()
{
	oepAltitudeSymbol::oepClamping res = oepAltitudeSymbol::oepClamping::ClampNone;

	if (as<AltitudeSymbol>()->clamping().isSet())
		return res;

	res = (oepAltitudeSymbol::oepClamping)(as<AltitudeSymbol>()->clamping().value());

	return res;
}

void oepAltitudeSymbol::Clamping::set(oepClamping p)
{
	as<AltitudeSymbol>()->clamping() = (AltitudeSymbol::Clamping)(p);
	NotifyChanged("Clamping");
}

oepAltitudeSymbol::oepTechnique oepAltitudeSymbol::Techinique::get()
{
	oepAltitudeSymbol::oepTechnique res = oepAltitudeSymbol::oepTechnique::TechniqueDrape;

	if (as<AltitudeSymbol>()->technique().isSet())
		return res;

	res = (oepAltitudeSymbol::oepTechnique)(as<AltitudeSymbol>()->technique().value());

	return res;
}

void oepAltitudeSymbol::Techinique::set(oepTechnique p)
{
	as<AltitudeSymbol>()->technique() = (AltitudeSymbol::Technique)(p);
	NotifyChanged("Techinique");
}

oepAltitudeSymbol::oepBinding oepAltitudeSymbol::Binding::get()
{
	oepAltitudeSymbol::oepBinding res = oepAltitudeSymbol::oepBinding::BindingCentroid;

	if (as<AltitudeSymbol>()->binding().isSet())
		return res;

	res = (oepAltitudeSymbol::oepBinding)(as<AltitudeSymbol>()->binding().value());

	return res;
}

void oepAltitudeSymbol::Binding::set(oepBinding p)
{
	as<AltitudeSymbol>()->binding() = (AltitudeSymbol::Binding)(p);
	NotifyChanged("Binding");
}

float oepAltitudeSymbol::ClampingResolution::get()
{
	if (as<AltitudeSymbol>()->clampingResolution().isSet())
		return 0.0f;
	return as<AltitudeSymbol>()->clampingResolution().value();
}

void oepAltitudeSymbol::ClampingResolution::set(float p)
{
	as<AltitudeSymbol>()->clampingResolution() = p;
	NotifyChanged("ClampingResolution");
}

oepNumericExpression^ oepAltitudeSymbol::VerticalOffset::get()
{
	return _verticalOffset;
}

void oepAltitudeSymbol::VerticalOffset::set(oepNumericExpression^ p)
{
	AltitudeSymbol* to = as<AltitudeSymbol>();
	if (to != NULL && p != nullptr)
	{
		to->verticalOffset() = *(p->as<NumericExpression>());
		NotifyChanged("VerticalOffset");
	}
}

oepNumericExpression^ oepAltitudeSymbol::VerticalScale::get()
{
	return _verticalScale;
}

void oepAltitudeSymbol::VerticalScale::set(oepNumericExpression^ p)
{
	AltitudeSymbol* to = as<AltitudeSymbol>();
	if (to != NULL && p != nullptr)
	{
		to->verticalScale() = *(p->as<NumericExpression>());
		NotifyChanged("VerticalScale");
	}
}

