#include "stdafx.h"
#include "MeasureVolumeHandler.h"
#include "CalcMath.h"
#define LC "[MeasureAreaHandler]"

using namespace gEarthPack;
using namespace osgEarth;
using namespace osgEarth::Util;
using namespace osgEarth::Symbology;
using namespace osgEarth::Features;
using namespace osgEarth::Annotation;

MeasureVolumeHandler::MeasureVolumeHandler() : 
_bnewmeasure(true),
_deep(10.0)
{

}


MeasureVolumeHandler::~MeasureVolumeHandler()
{
}

bool MeasureVolumeHandler::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	if (ea.getHandled())
	{
		return false;
	}

	osgViewer::View* view = static_cast<osgViewer::View*>(aa.asView());
	if (ea.getEventType() == osgGA::GUIEventAdapter::RELEASE)
	{
		if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
		{
			if (_bnewmeasure)
				clear();
			osg::Vec3d p, n;
			if (getLocationAt(view, ea.getX(), ea.getY(), p, n))
			{
				if (_feature->getGeometry()->size() > 0)
					_feature->getGeometry()->back() = p;
				else
					_feature->getGeometry()->push_back(p);


				_featureNode->init();

				fireMeasureChanged();
				_feature->getGeometry()->push_back(p);
				_bnewmeasure = false;
				aa.requestRedraw();
			}
		}
		else if (ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
		{
			_bnewmeasure = true;
		}
	}
	else if (ea.getEventType() == osgGA::GUIEventAdapter::MOVE)
	{
		if(!_bnewmeasure)
		{
			osg::Vec3d p, n;
			if (getLocationAt(view, ea.getX(), ea.getY(), p, n))
			{
				_feature->getGeometry()->back() = p;
				double d = (*(_feature->getGeometry()->end() - 2) - p).length();
				if (!osg::equivalent(d, 0.0, 1.0))
					_featureNode->init();
				aa.requestRedraw();
			}
		}
	}
	return false;
}

void MeasureVolumeHandler::clear()
{
	MeasureBaseHandler::clear();
}

void MeasureVolumeHandler::fireMeasureChanged()
{
	double volueme = 0;
	if (getGeoInterpolation() == GEOINTERP_GREAT_CIRCLE)
	{
		volueme = CalcMath::calcVolume(_feature->getGeometry()->asVector(), getMapNode(), _deep);
	}
	else if (getGeoInterpolation() == GEOINTERP_RHUMB_LINE)
	{
		volueme = CalcMath::calcRhumbVolume(_feature->getGeometry()->asVector(), getMapNode(), _deep);
	}
	for (ResultHandlers::const_iterator i = _reshandlers.begin(); i != _reshandlers.end(); ++i)
	{
		i->get()->onVolumeChanged(this, volueme);
	}
}

osgEarth::Features::Feature* MeasureVolumeHandler::createFeature()
{
	// Define the path feature:
	Feature* feature = new Feature(new osgEarth::Symbology::Polygon(), getMapNode()->getMapSRS());
	feature->geoInterp() = getGeoInterpolation();

	// clamp to the terrain skin as it pages in
	AltitudeSymbol* alt = feature->style()->getOrCreate<AltitudeSymbol>();
	alt->clamping() = alt->CLAMP_TO_TERRAIN;
	alt->technique() = alt->TECHNIQUE_DRAPE;

	// offset to mitigate Z fighting
	RenderSymbol* render = feature->style()->getOrCreate<RenderSymbol>();
	render->depthOffset()->enabled() = true;
	render->depthOffset()->automatic() = true;

	// define a style for the line
	LineSymbol* ls = feature->style()->getOrCreate<LineSymbol>();
	ls->stroke()->color() = Color::Yellow;
	ls->stroke()->width() = 2.0f;
	ls->stroke()->widthUnits() = Units::PIXELS;
	ls->tessellation() = 150;

	PolygonSymbol* ps = feature->style()->getOrCreate<PolygonSymbol>();
	ps->fill()->color() = Color(Color::Green, 0.5);

	return feature;
}

void gEarthPack::MeasureVolumeHandler::setDeep(double d)
{
	_deep = d;
	fireMeasureChanged();
}

double gEarthPack::MeasureVolumeHandler::getDeep() const
{
	return _deep;
}
