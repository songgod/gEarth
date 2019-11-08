#include "stdafx.h"
#include "MeasureProfileHandler.h"

using namespace gEarthPack;
using namespace osgEarth;
using namespace osgEarth::Util;
using namespace osgEarth::Symbology;
using namespace osgEarth::Features;
using namespace osgEarth::Annotation;

MeasureProfileHandler::MeasureProfileHandler(osgEarth::MapNode* mapNode) :MeasureBaseHandler(mapNode), _startValid(false)
{
	setMapNode(mapNode);
	_profileCalculator = new TerrainProfileCalculator(mapNode,
		GeoPoint(mapNode->getMapSRS(), 0, 0),
		GeoPoint(mapNode->getMapSRS(), 0, 0));
}


MeasureProfileHandler::~MeasureProfileHandler()
{
}

bool gEarthPack::MeasureProfileHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	if (ea.getEventType() == ea.PUSH && ea.getButton() == _mouseButton)
	{
		osg::Vec3d world;
		if (_mapNode->getTerrain()->getWorldCoordsUnderMouse(aa.asView(), ea.getX(), ea.getY(), world))
		{
			GeoPoint mapPoint;
			mapPoint.fromWorld(_mapNode->getMapSRS(), world);
			if (!_startValid)
			{
				clear();
				_startValid = true;
				_feature->getGeometry()->push_back(mapPoint.vec3d());
				_feature->getGeometry()->push_back(mapPoint.vec3d());
			}
			else
			{
				_startValid = false;
				fireMeasureChanged();
			}
		}
	}
	else if(ea.getEventType() == ea.MOVE && _startValid)
	{
		osg::Vec3d world;
		if (_mapNode->getTerrain()->getWorldCoordsUnderMouse(aa.asView(), ea.getX(), ea.getY(), world))
		{
			GeoPoint mapPoint;
			mapPoint.fromWorld(_mapNode->getMapSRS(), world);
			_feature->getGeometry()->back() = mapPoint.vec3d();
			_featureNode->init();
		}
	}
	return false;
}

osgEarth::Features::Feature* gEarthPack::MeasureProfileHandler::createFeature()
{
	LineString* line = new LineString();
	Feature* feature = new Feature(line, _mapNode->getMapSRS());
	feature->geoInterp() = GEOINTERP_GREAT_CIRCLE;

	//Define a style for the line
	Style style;
	LineSymbol* ls = style.getOrCreateSymbol<LineSymbol>();
	ls->stroke()->color() = Color::Yellow;
	ls->stroke()->width() = 3.0f;
	ls->tessellationSize()->set(100.0, Units::KILOMETERS);

	AltitudeSymbol* alt = style.getOrCreate<AltitudeSymbol>();
	alt->clamping() = alt->CLAMP_TO_TERRAIN;
	alt->technique() = alt->TECHNIQUE_DRAPE;

	RenderSymbol* render = style.getOrCreate<RenderSymbol>();
	render->lighting() = false;

	feature->style() = style;

	return feature;
}

void gEarthPack::MeasureProfileHandler::fireMeasureChanged()
{
	osg::Vec3d start, end;
	if (_feature->getGeometry()->size() == 2)
	{
		start = _feature->getGeometry()->at(0);
		end = _feature->getGeometry()->at(1);
	}
	_profileCalculator->setStartEnd(GeoPoint(_mapNode->getMapSRS(), start.x(), start.y()),
		GeoPoint(_mapNode->getMapSRS(), end.x(), end.y()));
}

void gEarthPack::MeasureProfileHandler::clear()
{
	_startValid = false;
	MeasureBaseHandler::clear();
}
