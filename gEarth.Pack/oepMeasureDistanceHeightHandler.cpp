#include "stdafx.h"
#include "MeasureDistanceHeightHandler.h"
#include "oepMeasureDistanceHeightHandler.h"
#include "oepHandleMapManager.h"

using namespace gEarthPack;
using namespace osgEarth::Symbology;

namespace
{
	class MeasureDistanceToolCallback : public MeasureDistanceHeightHandler::MeasureToolEventHandler
	{
	public:
		MeasureDistanceToolCallback()
		{
		}

		virtual void onDistanceHeightChanged(MeasureDistanceHeightHandler* sender, double distance, double height)
		{
			oepMeasureDistanceHeightHandler^ handle = oepHandleMapManager::getHandle<oepMeasureDistanceHeightHandler>(sender);
			if (handle == nullptr)
				return;
			handle->Distance = distance;
			handle->Height = height;
		}
	};
}

oepMeasureDistanceHeightHandler::oepMeasureDistanceHeightHandler() : _distance(0.0),_height(0.0)
{
	
}

void oepMeasureDistanceHeightHandler::bind(osgEarth::MapNode* pMapNode)
{
	MeasureDistanceHeightHandler* mth = new MeasureDistanceHeightHandler(pMapNode);
	mth->addEventHandler(new MeasureDistanceToolCallback());
	_handle->setValue(mth);
	oepHandleMapManager::registerHandle(mth,this);
	
	mth->setIntersectionMask(0x1);

	_nodemask = pMapNode->getNodeMask();
	pMapNode->setNodeMask(0x1);
}

void oepMeasureDistanceHeightHandler::unbind(osgEarth::MapNode* pMapNode)
{
	MeasureDistanceHeightHandler* handle = as<MeasureDistanceHeightHandler>();
	if (!handle)
		return;
	
	if (handle->getMapNode())
	{
		handle->getMapNode()->setNodeMask(_nodemask);
	}
	handle->setMapNode(NULL);
	oepHandleMapManager::unRegisterHandle(handle);
}

double oepMeasureDistanceHeightHandler::Distance::get()
{
	return _distance;
}

void oepMeasureDistanceHeightHandler::Distance::set(double d)
{
	_distance = d;
	NotifyChanged("Distance");
}

double gEarthPack::oepMeasureDistanceHeightHandler::Height::get()
{
	return _height;
}

void gEarthPack::oepMeasureDistanceHeightHandler::Height::set(double d)
{
	_height = d;
	NotifyChanged("Height");
}

bool oepMeasureDistanceHeightHandler::bPath::get()
{
	MeasureDistanceHeightHandler* handle = as<MeasureDistanceHeightHandler>();
	if (!handle)
		return false;

	return handle->getIsPath();
}

void oepMeasureDistanceHeightHandler::bPath::set(bool b)
{
	MeasureDistanceHeightHandler* handle = as<MeasureDistanceHeightHandler>();
	if (!handle)
		return;

	handle->setIsPath(b);
	NotifyChanged("bPath");
}

bool oepMeasureDistanceHeightHandler::bGreatCircle::get()
{
	MeasureDistanceHeightHandler* handle = as<MeasureDistanceHeightHandler>();
	if (!handle)
		return false;

	return handle->getGeoInterpolation() == osgEarth::GEOINTERP_GREAT_CIRCLE;
}

void oepMeasureDistanceHeightHandler::bGreatCircle::set(bool b)
{
	MeasureDistanceHeightHandler* handle = as<MeasureDistanceHeightHandler>();
	if (!handle)
		return;
	if (b)
		handle->setGeoInterpolation(osgEarth::GEOINTERP_GREAT_CIRCLE);
	else
		handle->setGeoInterpolation(osgEarth::GEOINTERP_RHUMB_LINE);
	NotifyChanged("bGreatCircle");
}
