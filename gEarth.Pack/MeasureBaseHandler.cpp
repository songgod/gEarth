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
	assert(_feature.valid());

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

bool MeasureBaseHandler::getLocationAt(osgViewer::View* view, double x, double y, osg::Vec3d& p, osg::Vec3d& n)
{
	if (!getMapNode())
		return false;

	if (!view->getCamera())
	{
		return false;
	}

	osgUtil::LineSegmentIntersector::Intersections intersections;
	if (view->computeIntersections(x, y, intersections))
	{
		const osgUtil::LineSegmentIntersector::Intersection& hit = *intersections.begin();

		osg::Vec3d point = hit.getWorldIntersectPoint();

		p = xyz2latlnghigh(point);
		n = hit.getWorldIntersectNormal();
		return true;
	}

	return false;
}

osg::Vec3d MeasureBaseHandler::xyz2latlnghigh(const osg::Vec3d& xyz)
{
	double lat = 0.0;
	double lng = 0.0;
	double height = 0.0;
	getMapNode()->getMap()->getProfile()->getSRS()->getEllipsoid()->convertXYZToLatLongHeight(
		xyz.x(), xyz.y(), xyz.z(), lat, lng, height);
	osg::Vec3d res;
	res.x() = osg::RadiansToDegrees(lng);
	res.y() = osg::RadiansToDegrees(lat);
	res.z() = height;
	return res;
}

osg::Vec3d MeasureBaseHandler::latlnghigh2xyz(const osg::Vec3d& llh)
{
	osg::Vec3d res;
	double lat = osg::DegreesToRadians(llh.y());
	double lng = osg::DegreesToRadians(llh.x());;
	double height = llh.z();
	getMapNode()->getMap()->getProfile()->getSRS()->getEllipsoid()->convertLatLongHeightToXYZ(
		lat, lng, height, res.x(), res.y(), res.z());
	return res;
}
