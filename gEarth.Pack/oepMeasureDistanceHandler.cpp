#include "stdafx.h"
#include "oepMeasureDistanceHandler.h"
#include "HandleMapManager.h"
using namespace System::Collections::Generic;

namespace
{
	class MeasureDistanceToolCallback : public MeasureToolHandler::MeasureToolEventHandler
	{
	public:
		MeasureDistanceToolCallback()
		{
		}

		virtual void onDistanceChanged(MeasureToolHandler* sender, double distance)
		{
			gEarthPack::oepMeasureDistanceHandler^ handle = gEarthPack::HandleMapManager::getHandle<gEarthPack::oepMeasureDistanceHandler>(sender);
			if (handle == nullptr)
				return;
			handle->Distance = distance;
		}
	};
}

gEarthPack::oepMeasureDistanceHandler::oepMeasureDistanceHandler() : _distance(0.0)
{
	
}

MeasureToolHandler* gEarthPack::oepMeasureDistanceHandler::asMesureDistanceHandler()
{
	return dynamic_cast<MeasureToolHandler*>(_handle->getValue());
}

void gEarthPack::oepMeasureDistanceHandler::bind(osgEarth::MapNode* pMapNode)
{
	MeasureToolHandler* mth = new MeasureToolHandler(pMapNode);
	mth->addEventHandler(new MeasureDistanceToolCallback());
	_handle->setValue(mth);
	gEarthPack::HandleMapManager::registerHandle(mth,this);
	
	mth->setIntersectionMask(0x1);

	_nodemask = pMapNode->getNodeMask();
	pMapNode->setNodeMask(0x1);
	Style style = mth->getLineStyle();
	style.getOrCreate<LineSymbol>()->stroke()->width() = 1.0f;
	style.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
	style.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_GPU;
	mth->setLineStyle(style);
}

void gEarthPack::oepMeasureDistanceHandler::unbind(osgEarth::MapNode* pMapNode)
{
	MeasureToolHandler* handle = asMesureDistanceHandler();
	if (!handle)
		return;
	
	if (handle->getMapNode())
	{
		handle->getMapNode()->setNodeMask(_nodemask);
	}
	handle->setMapNode(NULL);
	gEarthPack::HandleMapManager::unRegisterHandle(handle);
}

double gEarthPack::oepMeasureDistanceHandler::Distance::get()
{
	return _distance;
}

void gEarthPack::oepMeasureDistanceHandler::Distance::set(double d)
{
	_distance = d;
	NotifyChanged("Distance");
}

bool gEarthPack::oepMeasureDistanceHandler::bPath::get()
{
	MeasureToolHandler* handle = asMesureDistanceHandler();
	if (!handle)
		return false;

	return handle->getIsPath();
}

void gEarthPack::oepMeasureDistanceHandler::bPath::set(bool b)
{
	MeasureToolHandler* handle = asMesureDistanceHandler();
	if (!handle)
		return;

	handle->setIsPath(b);
	NotifyChanged("bPath");
}

bool gEarthPack::oepMeasureDistanceHandler::bGreatCircle::get()
{
	MeasureToolHandler* handle = asMesureDistanceHandler();
	if (!handle)
		return false;

	return handle->getGeoInterpolation() == osgEarth::GEOINTERP_GREAT_CIRCLE;
}

void gEarthPack::oepMeasureDistanceHandler::bGreatCircle::set(bool b)
{
	MeasureToolHandler* handle = asMesureDistanceHandler();
	if (!handle)
		return;
	if (b)
		handle->setGeoInterpolation(osgEarth::GEOINTERP_GREAT_CIRCLE);
	else
		handle->setGeoInterpolation(osgEarth::GEOINTERP_RHUMB_LINE);
	NotifyChanged("bGreatCircle");
}
