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

MeasureVolumeHandler::MeasureVolumeHandler(osgEarth::MapNode* mapNode) : MeasureBaseHandler(mapNode),
_mouseDown(false),
_gotFirstLocation(false),
_lastPointTemporary(false),
_finished(false),
_deep(0.0)
{
	setMapNode(mapNode);
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
	if (ea.getEventType() == osgGA::GUIEventAdapter::PUSH && ea.getButton() == _mouseButton)
	{
		_mouseDown = true;
		_mouseDownX = ea.getX();
		_mouseDownY = ea.getY();
	}
	else if (ea.getEventType() == osgGA::GUIEventAdapter::RELEASE && ea.getButton() == _mouseButton)
	{
		float eps = 1.0f;
		_mouseDown = false;
		if (osg::equivalent(ea.getX(), _mouseDownX, eps) && osg::equivalent(ea.getY(), _mouseDownY, eps))
		{
			osg::Vec3d p, n;
			if (getLocationAt(view, ea.getX(), ea.getY(), p, n))
			{
				if (!_gotFirstLocation)
				{
					_finished = false;
					clear();
					_gotFirstLocation = true;
					_feature->getGeometry()->push_back(p);
				}
				else
				{
					if (_lastPointTemporary)
					{
						_feature->getGeometry()->back() = p;
						_lastPointTemporary = false;
					}
					else
					{
						_feature->getGeometry()->push_back(p);
					}
					_featureNode->init();

					//_gotFirstLocation = false;
					//_finished = true;
					if (_finished) {
						_gotFirstLocation = false;
					}

					fireMeasureChanged();
					aa.requestRedraw();
				}
			}
		}
	}
	else if (ea.getEventType() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON) {
		if (_gotFirstLocation)
		{
			//_gotFirstLocation = false;
			_finished = true;
			aa.requestRedraw();
			return true;
		}
	}
	else if (ea.getEventType() == osgGA::GUIEventAdapter::MOVE)
	{
		if (_gotFirstLocation)
		{
			osg::Vec3d p, n;
			if (getLocationAt(view, ea.getX(), ea.getY(), p, n))
			{
				if (!_lastPointTemporary)
				{
					_feature->getGeometry()->push_back(p);
					_lastPointTemporary = true;
				}
				else
				{
					_feature->getGeometry()->back() = p;
				}
				_featureNode->init();
				//fireMeasureChanged();
				aa.requestRedraw();
			}
		}
	}
	return false;
}

void MeasureVolumeHandler::clear()
{
	_gotFirstLocation = false;
	_lastPointTemporary = false;
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

float gEarthPack::MeasureVolumeHandler::getDeep() const
{
	return _deep;
}
