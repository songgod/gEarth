#include "stdafx.h"

#include "MouseEventHandler.h"

using namespace osgEarth;
using namespace gEarthPack;

MouseEventHandler::MouseEventHandler():_mapNode(NULL)
{
}


MouseEventHandler::~MouseEventHandler()
{
}

bool MouseEventHandler::getGeoPoint(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa, osg::Vec3d& point)
{
	osg::Vec3d world;
	if (_mapNode->getTerrain()->getWorldCoordsUnderMouse(aa.asView(), ea.getX(), ea.getY(), world))
	{
		GeoPoint map;
		map.fromWorld(_mapNode->getMapSRS(), world);
		point = map.vec3d();
		return true;
	}
	return false;
}

bool MouseEventHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	if (_callbacks.empty())
		return false;

	switch (ea.getEventType())
	{
	case osgGA::GUIEventAdapter::EventType::PUSH:
	{
		osg::Vec3d p;
		if (getGeoPoint(ea, aa, p))
		{
			for (size_t i = 0; i < _callbacks.size(); i++)
			{
				_callbacks[i]->onMouseDown(this, p, ea.getButton());
			}
		}
		break;
	}
		
	case osgGA::GUIEventAdapter::EventType::RELEASE:
	{
		osg::Vec3d p;
		if (getGeoPoint(ea, aa, p))
		{
			for (size_t i = 0; i < _callbacks.size(); i++)
			{
				_callbacks[i]->onMouseUp(this, p, ea.getButton());
			}
		}
		break;
	}
	case osgGA::GUIEventAdapter::EventType::DOUBLECLICK:
	{
		osg::Vec3d p;
		if (getGeoPoint(ea, aa, p))
		{
			for (size_t i = 0; i < _callbacks.size(); i++)
			{
				_callbacks[i]->onMouseDoubleClick(this, p, ea.getButton());
			}
		}
		break;
	}
	case osgGA::GUIEventAdapter::EventType::DRAG:
	{
		osg::Vec3d p;
		if (getGeoPoint(ea, aa, p))
		{
			for (size_t i = 0; i < _callbacks.size(); i++)
			{
				_callbacks[i]->onMouseDrag(this, p, ea.getButton());
			}
		}
		break;
	}
	case osgGA::GUIEventAdapter::EventType::MOVE:
	{
		osg::Vec3d p;
		if (getGeoPoint(ea, aa, p))
		{
			for (size_t i = 0; i < _callbacks.size(); i++)
			{
				_callbacks[i]->onMouseMove(this, p, ea.getButton());
			}
		}
		break;
	}
	default:
		break;
	}
	return false;
}
