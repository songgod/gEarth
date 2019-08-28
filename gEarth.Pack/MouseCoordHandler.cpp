#include "stdafx.h"

#include "MouseCoordHandler.h"

using namespace osgEarth;
using namespace gEarthPack;

MouseCoordHandler::MouseCoordHandler():_mapNode(NULL)
{
}


MouseCoordHandler::~MouseCoordHandler()
{
}

void MouseCoordHandler::addMoveCallback(MouseMoveCallback* callback)
{
	if(callback)
		_callbacks.push_back(callback);
}

bool MouseCoordHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
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
