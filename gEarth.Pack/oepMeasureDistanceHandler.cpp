#include "stdafx.h"
#include "oepMeasureDistanceHandler.h"
#include "oepHandleMapManager.h"

using namespace gEarthPack;
using namespace osgEarth::Symbology;

namespace
{
	class MeasureDistanceToolCallback : public osgEarth::Util::MeasureToolHandler::MeasureToolEventHandler
	{
	public:
		MeasureDistanceToolCallback()
		{
		}

		virtual void onDistanceChanged(osgEarth::Util::MeasureToolHandler* sender, double distance)
		{
			oepMeasureDistanceHandler^ handle = oepHandleMapManager::getHandle<oepMeasureDistanceHandler>(sender);
			if (handle == nullptr)
				return;
			handle->Distance = distance;
		}
	};
}

oepMeasureDistanceHandler::oepMeasureDistanceHandler() : _distance(0.0)
{
	
}

osgEarth::Util::MeasureToolHandler* oepMeasureDistanceHandler::asMesureDistanceHandler()
{
	return dynamic_cast<osgEarth::Util::MeasureToolHandler*>(_handle->getValue());
}

void oepMeasureDistanceHandler::bind(osgEarth::MapNode* pMapNode)
{
	osgEarth::Util::MeasureToolHandler* mth = new osgEarth::Util::MeasureToolHandler(pMapNode);
	mth->addEventHandler(new MeasureDistanceToolCallback());
	_handle->setValue(mth);
	oepHandleMapManager::registerHandle(mth,this);
	
	mth->setIntersectionMask(0x1);

	_nodemask = pMapNode->getNodeMask();
	pMapNode->setNodeMask(0x1);
	Style style = mth->getLineStyle();
	style.getOrCreate<LineSymbol>()->stroke()->width() = 1.0f;
	style.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
	style.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_GPU;
	mth->setLineStyle(style);
}

void oepMeasureDistanceHandler::unbind(osgEarth::MapNode* pMapNode)
{
	osgEarth::Util::MeasureToolHandler* handle = asMesureDistanceHandler();
	if (!handle)
		return;
	
	if (handle->getMapNode())
	{
		handle->getMapNode()->setNodeMask(_nodemask);
	}
	handle->setMapNode(NULL);
	oepHandleMapManager::unRegisterHandle(handle);
}

double oepMeasureDistanceHandler::Distance::get()
{
	return _distance;
}

void oepMeasureDistanceHandler::Distance::set(double d)
{
	_distance = d;
	NotifyChanged("Distance");
}

bool oepMeasureDistanceHandler::bPath::get()
{
	osgEarth::Util::MeasureToolHandler* handle = asMesureDistanceHandler();
	if (!handle)
		return false;

	return handle->getIsPath();
}

void oepMeasureDistanceHandler::bPath::set(bool b)
{
	osgEarth::Util::MeasureToolHandler* handle = asMesureDistanceHandler();
	if (!handle)
		return;

	handle->setIsPath(b);
	NotifyChanged("bPath");
}

bool oepMeasureDistanceHandler::bGreatCircle::get()
{
	osgEarth::Util::MeasureToolHandler* handle = asMesureDistanceHandler();
	if (!handle)
		return false;

	return handle->getGeoInterpolation() == osgEarth::GEOINTERP_GREAT_CIRCLE;
}

void oepMeasureDistanceHandler::bGreatCircle::set(bool b)
{
	osgEarth::Util::MeasureToolHandler* handle = asMesureDistanceHandler();
	if (!handle)
		return;
	if (b)
		handle->setGeoInterpolation(osgEarth::GEOINTERP_GREAT_CIRCLE);
	else
		handle->setGeoInterpolation(osgEarth::GEOINTERP_RHUMB_LINE);
	NotifyChanged("bGreatCircle");
}
