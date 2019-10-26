#include "stdafx.h"
#include "MeasureAngleHandler.h"

#define LC "[MeasureTool] "

using namespace gEarthPack;
using namespace osgEarth;
using namespace osgEarth::Util;
using namespace osgEarth::Symbology;
using namespace osgEarth::Features;
using namespace osgEarth::Annotation;

MeasureAngleHandler::MeasureAngleHandler(osgEarth::MapNode* mapNode):
	_geoInterpolation(GEOINTERP_GREAT_CIRCLE),
	_mouseButton(osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON),
	_intersectionMask(0xffffffff),
	_bNewMesura(true)
{
	_root = new osg::Group();
	setMapNode(mapNode);
}


MeasureAngleHandler::~MeasureAngleHandler()
{
	setMapNode(0L);
}

void MeasureAngleHandler::setMapNode(osgEarth::MapNode* mapNode)
{
	MapNode* oldMapNode = getMapNode();

	if (oldMapNode != mapNode)
	{
		if (oldMapNode)
		{
			oldMapNode->removeChild(_root.get());
		}

		_mapNode = mapNode;

		if (mapNode)
		{
			mapNode->addChild(_root.get());
		}

		rebuild();
	}
}

void MeasureAngleHandler::rebuild()
{
	if (_featureNode.valid())
	{
		_root->removeChild(_featureNode.get());
		_featureNode = 0L;
	}

	if (!getMapNode())
		return;

	if (getMapNode()->getMapSRS()->isProjected())
	{
		OE_WARN << LC << "Sorry, MeasureTool does not yet support projected maps" << std::endl;
		return;
	}


	// Define the path feature:
	_feature = new Feature(new LineString(), getMapNode()->getMapSRS());
	_feature->geoInterp() = _geoInterpolation;

	// clamp to the terrain skin as it pages in
	AltitudeSymbol* alt = _feature->style()->getOrCreate<AltitudeSymbol>();
	alt->clamping() = alt->CLAMP_TO_TERRAIN;
	alt->technique() = alt->TECHNIQUE_GPU;

	// offset to mitigate Z fighting
	RenderSymbol* render = _feature->style()->getOrCreate<RenderSymbol>();
	render->depthOffset()->enabled() = true;
	render->depthOffset()->automatic() = true;

	// define a style for the line
	LineSymbol* ls = _feature->style()->getOrCreate<LineSymbol>();
	ls->stroke()->color() = Color::Yellow;
	ls->stroke()->width() = 2.0f;
	ls->stroke()->widthUnits() = Units::PIXELS;
	ls->tessellation() = 150;

	_featureNode = new FeatureNode(_feature.get());
	_featureNode->setMapNode(getMapNode());

	GLUtils::setLighting(_featureNode->getOrCreateStateSet(), osg::StateAttribute::OFF);
	//_featureNode->setClusterCulling(false);

	_root->addChild(_featureNode.get());
}

osgEarth::GeoInterpolation
MeasureAngleHandler::getGeoInterpolation() const
{
	return _geoInterpolation;
}

void
MeasureAngleHandler::setGeoInterpolation(osgEarth::GeoInterpolation geoInterpolation)
{
	if (_geoInterpolation != geoInterpolation)
	{
		_geoInterpolation = geoInterpolation;
		_feature->geoInterp() = _geoInterpolation;
		_featureNode->init();
		fireAngleChanged();
	}
}

bool 
MeasureAngleHandler::getLocationAt(osgViewer::View* view, double x, double y, double &lon, double &lat, double &height)
{
	osgUtil::LineSegmentIntersector::Intersections results;
	if (getMapNode() && view->computeIntersections(x, y, results, _intersectionMask))
	{
		// find the first hit under the mouse:
		osgUtil::LineSegmentIntersector::Intersection first = *(results.begin());
		osg::Vec3d point = first.getWorldIntersectPoint();

		double lat_rad, lon_rad;
		getMapNode()->getMap()->getProfile()->getSRS()->getEllipsoid()->convertXYZToLatLongHeight(
			point.x(), point.y(), point.z(), lat_rad, lon_rad, height);

		lat = osg::RadiansToDegrees(lat_rad);
		lon = osg::RadiansToDegrees(lon_rad);
		return true;
	}
	return false;
}

void MeasureAngleHandler::addEventHandler(MeasureAngleEventHandler* handler)
{
	_eventHandlers.push_back(handler);
}

bool MeasureAngleHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	if (ea.getHandled())
	{
		return false;
	}


	osgViewer::View* view = static_cast<osgViewer::View*>(aa.asView());
	if(ea.getEventType() == osgGA::GUIEventAdapter::RELEASE && ea.getButton() == _mouseButton)
	{
		if(_bNewMesura)
			clear();

		double lon, lat, height;
		if (getLocationAt(view, ea.getX(), ea.getY(), lon, lat, height))
		{
			if (_feature->getGeometry()->size() > 0)
				_feature->getGeometry()->back() = osg::Vec3d(lon, lat, height);
			else
				_feature->getGeometry()->push_back(osg::Vec3d(lon, lat, height));

			_bNewMesura = _feature->getGeometry()->size() == 3;

			if(_feature->getGeometry()->size()<3)
				_feature->getGeometry()->push_back(osg::Vec3d(lon, lat, height));
			_featureNode->init();
		}

		fireAngleChanged();
		aa.requestRedraw();
	}
	else if (ea.getEventType() == osgGA::GUIEventAdapter::MOVE)
	{
		if (!_bNewMesura)
		{
			double lon, lat, height;
			if (getLocationAt(view, ea.getX(), ea.getY(), lon, lat, height))
			{

				_feature->getGeometry()->back() = osg::Vec3d(lon, lat, height);
				_featureNode->init();
				fireAngleChanged();
				aa.requestRedraw();
			}
		}
	}
	return false;
}

void MeasureAngleHandler::fireAngleChanged()
{
	std::vector<osg::Vec3d> poss = _feature->getGeometry()->asVector();
	if (poss.size() != 3)
		return;

	double a = (poss[2] - poss[0]).length2();
	double b = (poss[1] - poss[0]).length2();
	double c = (poss[2] - poss[1]).length2();

	double cosangle = (b + c - a) / (sqrt(b)*sqrt(c) * 2);
	double angle = osg::RadiansToDegrees(acos(cosangle));

	for (MeasureAngleEventHandlerList::const_iterator i = _eventHandlers.begin(); i != _eventHandlers.end(); ++i)
	{
		i->get()->onAngleChanged(this, angle);
	}
}

void MeasureAngleHandler::clear()
{
	//Clear the locations    
	_feature->getGeometry()->clear();
	//_features->dirty();
	_featureNode->init();

	fireAngleChanged();
}
