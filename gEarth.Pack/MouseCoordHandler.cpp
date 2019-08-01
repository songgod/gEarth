#include "stdafx.h"
#include "MouseCoordHandler.h"
#include <osgEarth/MapNode>
#include <osgEarth/TerrainEngineNode>

using namespace osgEarth;


gEarthPack::MouseCoordHandler::MouseCoordHandler():_mapNode(NULL)
{
}


gEarthPack::MouseCoordHandler::~MouseCoordHandler()
{
}

void gEarthPack::MouseCoordHandler::addMoveCallback(MouseMoveCallback* callback)
{
	if(callback)
		_callbacks.push_back(callback);
}

bool gEarthPack::MouseCoordHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	if (_mapNode && ea.getEventType() == ea.MOVE || ea.getEventType() == ea.DRAG)
	{
		osg::Vec3d world;
		if (_mapNode->getTerrain()->getWorldCoordsUnderMouse(aa.asView(), ea.getX(), ea.getY(), world))
		{
			GeoPoint map;
			map.fromWorld(_mapNode->getMapSRS(), world);

			for (MoveCallbacks::iterator i = _callbacks.begin(); i != _callbacks.end(); ++i)
				i->get()->update(this, osg::Vec3(map.x(),map.y(),map.z()));
		}
	}

	return false;
}
