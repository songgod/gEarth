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

MeasureDistanceHeightHandler::MeasureDistanceHeightHandler(osgEarth::MapNode* mapNode) :
	_mouseDown(false),
	_gotFirstLocation(false),
	_lastPointTemporary(false),
	_finished(false),
	_geoInterpolation(GEOINTERP_GREAT_CIRCLE),
	_mouseButton(osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON),
	_isPath(false),
	_intersectionMask(0xffffffff)
{
	_root = new osg::Group();
	setMapNode(mapNode);
}

MeasureDistanceHeightHandler::~MeasureDistanceHeightHandler()
{
	setMapNode(0L);
}


void
MeasureDistanceHeightHandler::setMapNode(MapNode* mapNode)
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


void
MeasureDistanceHeightHandler::rebuild()
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

#ifdef SHOW_EXTENT

	// Define the extent feature:
	_extentFeature = new Feature(new Polygon(), getMapNode()->getMapSRS());
	_extentFeature->geoInterp() = GEOINTERP_RHUMB_LINE;
	_extentFeature->style()->add(alt);
	LineSymbol* extentLine = _extentFeature->style()->getOrCreate<LineSymbol>();
	extentLine->stroke()->color() = Color::Cyan;
	extentLine->stroke()->width() = 2.0f;
	extentLine->tessellation() = 20;

	_extentFeatureNode = new FeatureNode(getMapNode(), _extentFeature.get());

	_root->addChild(_extentFeatureNode.get());
#endif
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


osgEarth::GeoInterpolation
MeasureDistanceHeightHandler::getGeoInterpolation() const
{
	return _geoInterpolation;
}

void
MeasureDistanceHeightHandler::setGeoInterpolation(osgEarth::GeoInterpolation geoInterpolation)
{
	if (_geoInterpolation != geoInterpolation)
	{
		_geoInterpolation = geoInterpolation;
		_feature->geoInterp() = _geoInterpolation;
		_featureNode->init();
		fireDistanceChanged();
	}
}

void
MeasureDistanceHeightHandler::setLineStyle(const osgEarth::Symbology::Style& style)
{
	_feature->style() = style;
	_featureNode->init();
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
			double lon, lat, height;
			if (getLocationAt(view, ea.getX(), ea.getY(), lon, lat, height))
			{
				if (!_gotFirstLocation)
				{
					_finished = false;
					clear();
					_gotFirstLocation = true;
					_feature->getGeometry()->push_back(osg::Vec3d(lon, lat, height));
				}
				else
				{
					if (_lastPointTemporary)
					{
						_feature->getGeometry()->back() = osg::Vec3d(lon, lat, height);
						_lastPointTemporary = false;
					}
					else
					{
						_feature->getGeometry()->push_back(osg::Vec3d(lon, lat, height));
					}
					_featureNode->init();

					//_gotFirstLocation = false;
					//_finished = true;
					if (_finished || !_isPath) {
						_gotFirstLocation = false;
					}

#ifdef SHOW_EXTENT
					const GeoExtent ex(_feature->getSRS(), _feature->getGeometry()->getBounds());
					//OE_INFO << "extent = " << ex.toString() << std::endl;
					Geometry* eg = _extentFeature->getGeometry();
					osg::Vec3d fc = ex.getCentroid();
					eg->clear();
					eg->push_back(ex.west(), ex.south());
					if (ex.width() >= 180.0)
						eg->push_back(fc.x(), ex.south());
					eg->push_back(ex.east(), ex.south());
					eg->push_back(ex.east(), ex.north());
					if (ex.width() >= 180.0)
						eg->push_back(fc.x(), ex.north());
					eg->push_back(ex.west(), ex.north());
					_extentFeatureNode->init();
#endif

					fireDistanceChanged();
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
			double lon, lat, height;
			if (getLocationAt(view, ea.getX(), ea.getY(), lon, lat, height))
			{
				if (!_lastPointTemporary)
				{
					_feature->getGeometry()->push_back(osg::Vec3d(lon, lat, height));
					_lastPointTemporary = true;
				}
				else
				{
					_feature->getGeometry()->back() = osg::Vec3d(lon, lat, height);
				}
				_featureNode->init();
				fireDistanceChanged();
				aa.requestRedraw();
			}
		}
	}
	return false;
}

bool MeasureDistanceHeightHandler::getLocationAt(osgViewer::View* view, double x, double y, double &lon, double &lat, double &height)
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

void MeasureDistanceHeightHandler::clear()
{
	//Clear the locations    
	_feature->getGeometry()->clear();
	//_features->dirty();
	_featureNode->init();

#ifdef SHOW_EXTENT
	_extentFeature->getGeometry()->clear();
	_extentFeatureNode->init();
#endif

	fireDistanceChanged();

	_gotFirstLocation = false;
	_lastPointTemporary = false;
}

void
MeasureDistanceHeightHandler::setMouseButton(int mouseButton)
{
	_mouseButton = mouseButton;
}

int
MeasureDistanceHeightHandler::getMouseButton() const
{
	return _mouseButton;
}


void MeasureDistanceHeightHandler::addEventHandler(MeasureToolEventHandler* handler)
{
	_eventHandlers.push_back(handler);
}


void MeasureDistanceHeightHandler::fireDistanceChanged()
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
