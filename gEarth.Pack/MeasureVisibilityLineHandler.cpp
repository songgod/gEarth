#include "stdafx.h"
#include "MeasureVisibilityLineHandler.h"

using namespace gEarthPack;
using namespace osgEarth;
using namespace osgEarth::Util;
using namespace osgEarth::Symbology;
using namespace osgEarth::Features;
using namespace osgEarth::Annotation;

MeasureVisibilityLineHandler::MeasureVisibilityLineHandler(osgEarth::MapNode* mapNode):MeasureBaseHandler(mapNode), _startValid(false)
{
	setMapNode(mapNode);
}


MeasureVisibilityLineHandler::~MeasureVisibilityLineHandler()
{

}

void MeasureVisibilityLineHandler::rebuild()
{
	if (_lineofsightnode.valid())
	{
		_root->removeChild(_lineofsightnode.get());
		_lineofsightnode = 0L;
	}

	if (!getMapNode())
		return;

	if (getMapNode()->getMapSRS()->isProjected())
	{
		OE_WARN << "Sorry, MeasureTool does not yet support projected maps" << std::endl;
		return;
	}

	_lineofsightnode = new osgEarth::Util::LinearLineOfSightNode(_mapNode.get());
	_root->addChild(_lineofsightnode.get());
}

void MeasureVisibilityLineHandler::clear()
{
	_startValid = false;
	_lineofsightnode->setStart(osgEarth::GeoPoint());
	_lineofsightnode->setEnd(osgEarth::GeoPoint());
}

bool MeasureVisibilityLineHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
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
				_lineofsightnode->setStart(mapPoint);
				_lineofsightnode->setEnd(mapPoint);
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
			mapPoint.z() = 10;
			mapPoint.altitudeMode() = ALTMODE_RELATIVE;
			_lineofsightnode->setEnd(mapPoint);
		}
	}
	return false;
}
