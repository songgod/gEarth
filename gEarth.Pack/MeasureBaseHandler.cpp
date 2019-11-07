#include "stdafx.h"
#include "MeasureBaseHandler.h"
#include <assert.h>

using namespace gEarthPack;
using namespace osgEarth;
using namespace osgEarth::Util;
using namespace osgEarth::Symbology;
using namespace osgEarth::Features;
using namespace osgEarth::Annotation;

MeasureBaseHandler::MeasureBaseHandler(osgEarth::MapNode* mapNode) :
	_geoInterpolation(GEOINTERP_GREAT_CIRCLE),
	_mouseButton(osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON),
	_intersectionMask(0xffffffff)
{
	_root = new osg::Group();
	setMapNode(mapNode);
}


MeasureBaseHandler::~MeasureBaseHandler()
{
	setMapNode(0L);
}

void MeasureBaseHandler::setMapNode(osgEarth::MapNode* mapNode)
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

void MeasureBaseHandler::rebuild()
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
		OE_WARN << "Sorry, MeasureTool does not yet support projected maps" << std::endl;
		return;
	}

	_feature = createFeature();
	assert(_feature!=NULL);

	_featureNode = new FeatureNode(_feature.get());
	_featureNode->setMapNode(getMapNode());

	GLUtils::setLighting(_featureNode->getOrCreateStateSet(), osg::StateAttribute::OFF);
	//_featureNode->setClusterCulling(false);

	_root->addChild(_featureNode.get());
}

osgEarth::GeoInterpolation
MeasureBaseHandler::getGeoInterpolation() const
{
	return _geoInterpolation;
}

void
MeasureBaseHandler::setGeoInterpolation(osgEarth::GeoInterpolation geoInterpolation)
{
	if (_geoInterpolation != geoInterpolation)
	{
		_geoInterpolation = geoInterpolation;
		_feature->geoInterp() = _geoInterpolation;
		_featureNode->init();
		fireMeasureChanged();
	}
}

void MeasureBaseHandler::clear()
{
	//Clear the locations    
	_feature->getGeometry()->clear();
	//_features->dirty();
	_featureNode->init();

	fireMeasureChanged();
}

bool
MeasureBaseHandler::getLocationAt(osgViewer::View* view, double x, double y, double &lon, double &lat, double &height)
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

bool MeasureBaseHandler::getLocalNormalAt(osgViewer::View* view, double x, double y, osg::Vec3d& p, osg::Vec3d& n)
{
	if (!getMapNode())
		return false;

	osg::Vec3d eye, center, up;
	if (!view->getCamera())
	{
		return false;
	}

	view->getCamera()->getViewMatrixAsLookAt(eye, center, up);

	osgUtil::LineSegmentIntersector::Intersections intersections;
	if (view->computeIntersections(x, y, intersections))
	{
		const osgUtil::LineSegmentIntersector::Intersection& hit = *intersections.begin();

		osg::Vec3d point = hit.getWorldIntersectPoint();

		double lat_rad, lon_rad, height;
		getMapNode()->getMap()->getProfile()->getSRS()->getEllipsoid()->convertXYZToLatLongHeight(
			point.x(), point.y(), point.z(), lat_rad, lon_rad, height);

		p.x() = osg::RadiansToDegrees(lat_rad);
		p.y() = osg::RadiansToDegrees(lon_rad);
		p.z() = height;

		n = hit.getWorldIntersectNormal();
		return true;
	}

	return false;
}
