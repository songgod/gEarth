#include "stdafx.h"

#include "MeasureAreaHandler.h"
#include <osgEarth/MapNode>
#include <osgEarth/GLUtils>
#include <osgEarthSymbology/Geometry>

#define LC "[MeasureAreaHandler] "

using namespace gEarthPack;
using namespace osgEarth;
using namespace osgEarth::Annotation;
using namespace osgEarth::Features;
using namespace osgEarth::Symbology;

MeasureAreaHandler::MeasureAreaHandler(osgEarth::MapNode* pMapNode):
	_intersectionMask(0xffffffff), 
	_geointerpolation(GEOINTERP_GREAT_CIRCLE),
	_mouseDown(false),
	_gotFirstLocation(false),
	_lastPointTemporary(false),
	_finished(false),
	_mouseButton(osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
{
	_root = new osg::Group();	
	setMapNode(pMapNode);
}


MeasureAreaHandler::~MeasureAreaHandler()
{
	setMapNode(0L);
}

bool MeasureAreaHandler::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
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
			double lon, lat;
			if (getLocationAt(view, ea.getX(), ea.getY(), lon, lat))
			{
				if (!_gotFirstLocation)
				{
					_finished = false;
					clear();
					_gotFirstLocation = true;
					_feature->getGeometry()->push_back(osg::Vec3d(lon, lat, 0));
				}
				else
				{
					if (_lastPointTemporary)
					{
						_feature->getGeometry()->back() = osg::Vec3d(lon, lat, 0);
						_lastPointTemporary = false;
					}
					else
					{
						_feature->getGeometry()->push_back(osg::Vec3d(lon, lat, 0));
					}
					_featureNode->init();

					//_gotFirstLocation = false;
					//_finished = true;
					if (_finished) {
						_gotFirstLocation = false;
					}

					fireAreaChanged();
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
			double lon, lat;
			if (getLocationAt(view, ea.getX(), ea.getY(), lon, lat))
			{
				if (!_lastPointTemporary)
				{
					_feature->getGeometry()->push_back(osg::Vec3d(lon, lat, 0));
					_lastPointTemporary = true;
				}
				else
				{
					_feature->getGeometry()->back() = osg::Vec3d(lon, lat, 0);
				}
				_featureNode->init();
				fireAreaChanged();
				aa.requestRedraw();
			}
		}
	}
	return false;
}

bool MeasureAreaHandler::getLocationAt(osgViewer::View* view, double x, double y, double &lon, double &lat)
{
	osgUtil::LineSegmentIntersector::Intersections results;
	if (getMapNode() && view->computeIntersections(x, y, results, _intersectionMask))
	{
		// find the first hit under the mouse:
		osgUtil::LineSegmentIntersector::Intersection first = *(results.begin());
		osg::Vec3d point = first.getWorldIntersectPoint();

		double lat_rad, lon_rad, height;
		getMapNode()->getMap()->getProfile()->getSRS()->getEllipsoid()->convertXYZToLatLongHeight(
			point.x(), point.y(), point.z(), lat_rad, lon_rad, height);

		lat = osg::RadiansToDegrees(lat_rad);
		lon = osg::RadiansToDegrees(lon_rad);
		return true;
	}
	return false;
}

void MeasureAreaHandler::clear()
{
	//Clear the locations    
	_feature->getGeometry()->clear();
	//_features->dirty();
	_featureNode->init();

	fireAreaChanged();

	_gotFirstLocation = false;
	_lastPointTemporary = false;
}

void MeasureAreaHandler::setMapNode(osgEarth::MapNode* mapNode)
{
	MapNode* oldMapNode = getMapNode();

	if (oldMapNode != mapNode)
	{
		if (oldMapNode)
		{
			oldMapNode->removeChild(_root.get());
		}

		_mapnode = mapNode;

		if (mapNode)
		{
			mapNode->addChild(_root.get());
		}

		rebuild();
	}
}

osgEarth::GeoInterpolation MeasureAreaHandler::getGeoInterpolation() const
{
	return _geointerpolation;
}

void MeasureAreaHandler::fireAreaChanged()
{
	double distance = 0;
	if (_geointerpolation == GEOINTERP_GREAT_CIRCLE)
	{
		distance = GeoMath::distance(_feature->getGeometry()->asVector());
	}
	else if (_geointerpolation == GEOINTERP_RHUMB_LINE)
	{
		distance = GeoMath::rhumbDistance(_feature->getGeometry()->asVector());
	}
	for (ResultHandlers::const_iterator i = _reshandlers.begin(); i != _reshandlers.end(); ++i)
	{
		i->get()->onAreaChanged(this, distance);
	}
}

void MeasureAreaHandler::setGeoInterpolation(osgEarth::GeoInterpolation geoInterpolation)
{
	if (_geointerpolation != geoInterpolation)
	{
		_geointerpolation = geoInterpolation;
		_feature->geoInterp() = _geointerpolation;
		_featureNode->init();
		fireAreaChanged();
	}
}

void
MeasureAreaHandler::setMouseButton(int mouseButton)
{
	_mouseButton = mouseButton;
}

int
MeasureAreaHandler::getMouseButton() const
{
	return _mouseButton;
}

void MeasureAreaHandler::rebuild()
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
	_feature = new Feature(new osgEarth::Symbology::Polygon(), getMapNode()->getMapSRS());
	_feature->geoInterp() = _geointerpolation;

	// clamp to the terrain skin as it pages in
	AltitudeSymbol* alt = _feature->style()->getOrCreate<AltitudeSymbol>();
	alt->clamping() = alt->CLAMP_TO_TERRAIN;
	alt->technique() = alt->TECHNIQUE_DRAPE;

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

	PolygonSymbol* ps = _feature->style()->getOrCreate<PolygonSymbol>();
	ps->fill()->color() = Color(Color::Green, 0.5);

	_featureNode = new FeatureNode(_feature.get());
	_featureNode->setMapNode(getMapNode());

	GLUtils::setLighting(_featureNode->getOrCreateStateSet(), osg::StateAttribute::OFF);
	//_featureNode->setClusterCulling(false);

	_root->addChild(_featureNode.get());
}
