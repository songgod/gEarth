#include "stdafx.h"
#include "MeasureVisibilityAreaHandler.h"
#include <osg/Depth>
using namespace gEarthPack;
using namespace osgEarth;
using namespace osgEarth::Util;
using namespace osgEarth::Symbology;
using namespace osgEarth::Features;
using namespace osgEarth::Annotation;

MeasureVisibilityAreaHandler::MeasureVisibilityAreaHandler()
{

}


MeasureVisibilityAreaHandler::~MeasureVisibilityAreaHandler()
{

}

void MeasureVisibilityAreaHandler::rebuild()
{
	if (_radiaofsightnode.valid())
	{
		_root->removeChild(_radiaofsightnode.get());
		_radiaofsightnode = 0L;
	}

	if (!getMapNode())
		return;

	if (getMapNode()->getMapSRS()->isProjected())
	{
		OE_WARN << "Sorry, MeasureTool does not yet support projected maps" << std::endl;
		return;
	}

	_radiaofsightnode = new osgEarth::Util::RadialLineOfSightNode(_mapNode.get());
	_radiaofsightnode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	_radiaofsightnode->getOrCreateStateSet()->setAttributeAndModes(new osg::Depth(osg::Depth::ALWAYS, 0, 1, false));
	_radiaofsightnode->setNumSpokes(360);
	_radiaofsightnode->setGoodColor(osg::Vec4(0, 1, 0, 0.3));
	_radiaofsightnode->setBadColor(osg::Vec4(1, 0, 0, 0.3));
	//_radiaofsightnode->setFill(true);
	_root->addChild(_radiaofsightnode.get());
}

void MeasureVisibilityAreaHandler::clear()
{
	_startValid = false;
	_radiaofsightnode->setCenter(osgEarth::GeoPoint());
	_radiaofsightnode->setRadius(0.0);
}

bool MeasureVisibilityAreaHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{

	if (ea.getEventType() == ea.PUSH && ea.getButton() == _mouseButton)
	{
		osg::Vec3d world;
		if (_mapNode->getTerrain()->getWorldCoordsUnderMouse(aa.asView(), ea.getX(), ea.getY(), world))
		{
			GeoPoint mapPoint;
			mapPoint.fromWorld(_mapNode->getMapSRS(), world);
			mapPoint.z() = 10;
			mapPoint.altitudeMode() = ALTMODE_RELATIVE;
			if (!_startValid)
			{
				clear();
				_startValid = true;
				_radiaofsightnode->setCenter(mapPoint);
				_radiaofsightnode->setRadius(0.0);
			}
			else
			{
				_startValid = false;
				fireMeasureChanged();
			}
		}
	}
	else if (ea.getEventType() == ea.MOVE && _startValid)
	{
		osg::Vec3d world;
		if (_mapNode->getTerrain()->getWorldCoordsUnderMouse(aa.asView(), ea.getX(), ea.getY(), world))
		{
			GeoPoint mapPoint;
			mapPoint.fromWorld(_mapNode->getMapSRS(), world);

			std::vector<osg::Vec3d> poss;
			poss.push_back(_radiaofsightnode->getCenter().vec3d());
			poss.push_back(mapPoint.vec3d());
			double radius = GeoMath::distance(poss);
			_radiaofsightnode->setRadius(radius);
		}
	}
	return false;
}
