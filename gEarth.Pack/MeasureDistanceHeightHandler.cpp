#include "stdafx.h"
#include "MeasureDistanceHeightHandler.h"

#define LC "[MeasureTool] "

using namespace gEarthPack;
using namespace osgEarth;
using namespace osgEarth::Util;
using namespace osgEarth::Symbology;
using namespace osgEarth::Features;
using namespace osgEarth::Annotation;

//#define SHOW_EXTENT 1

MeasureDistanceHeightHandler::MeasureDistanceHeightHandler(osgEarth::MapNode* mapNode) : MeasureBaseHandler(mapNode),
	_mouseDown(false),
	_gotFirstLocation(false),
	_lastPointTemporary(false),
	_finished(false),
	_isPath(false)
{
	setMapNode(mapNode);
}

MeasureDistanceHeightHandler::~MeasureDistanceHeightHandler()
{
}

bool
MeasureDistanceHeightHandler::getIsPath() const
{
	return _isPath;
}

void
MeasureDistanceHeightHandler::setIsPath(bool path)
{
	if (_isPath != path)
	{
		_isPath = path;
		_finished = true;
		clear();
		_gotFirstLocation = false;
	}
}

bool MeasureDistanceHeightHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
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
					if (_finished || !_isPath) {
						_gotFirstLocation = false;
					}

					fireMeasureChanged();
					aa.requestRedraw();
				}
			}
		}
	}
	else if (ea.getEventType() == osgGA::GUIEventAdapter::DOUBLECLICK) {
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
				fireMeasureChanged();
				aa.requestRedraw();
			}
		}
	}
	return false;
}

void MeasureDistanceHeightHandler::clear()
{
	_gotFirstLocation = false;
	_lastPointTemporary = false;
	MeasureBaseHandler::clear();
}

void MeasureDistanceHeightHandler::addEventHandler(MeasureToolEventHandler* handler)
{
	_eventHandlers.push_back(handler);
}


void MeasureDistanceHeightHandler::fireMeasureChanged()
{
	double distance = 0;
	std::vector<osg::Vec3d> poss = _feature->getGeometry()->asVector();
	double height = 0.0;
	if (poss.size() > 0)
		height = poss[poss.size() - 1].z() - poss[0].z();
	if (_geoInterpolation == GEOINTERP_GREAT_CIRCLE)
	{
		distance = GeoMath::distance(poss);
	}
	else if (_geoInterpolation == GEOINTERP_RHUMB_LINE)
	{
		distance = GeoMath::rhumbDistance(poss);
	}
	for (MeasureToolEventHandlerList::const_iterator i = _eventHandlers.begin(); i != _eventHandlers.end(); ++i)
	{
		i->get()->onDistanceHeightChanged(this, distance,height);
	}
}

osgEarth::Features::Feature* MeasureDistanceHeightHandler::createFeature()
{
	// Define the path feature:
	Feature* feature = new Feature(new LineString(), getMapNode()->getMapSRS());
	feature->geoInterp() = _geoInterpolation;

	// clamp to the terrain skin as it pages in
	AltitudeSymbol* alt = feature->style()->getOrCreate<AltitudeSymbol>();
	alt->clamping() = alt->CLAMP_TO_TERRAIN;
	alt->technique() = alt->TECHNIQUE_GPU;

	// offset to mitigate Z fighting
	RenderSymbol* render = feature->style()->getOrCreate<RenderSymbol>();
	render->depthOffset()->enabled() = true;
	render->depthOffset()->automatic() = true;

	// define a style for the line
	LineSymbol* ls = feature->style()->getOrCreate<LineSymbol>();
	ls->stroke()->color() = Color::Yellow;
	ls->stroke()->width() = 1.0f;
	ls->stroke()->widthUnits() = Units::PIXELS;
	ls->tessellation() = 150;

	return feature;
}
