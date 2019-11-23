#include "stdafx.h"
#include "oepMeasureAngleHandler.h"
#include "MeasureAngleHandler.h"
#include "oepHandleMapManager.h"

using namespace gEarthPack;

namespace
{
	class MeasureAngleToolCallback : public MeasureAngleHandler::MeasureAngleEventHandler
	{
	public:
		MeasureAngleToolCallback()
		{
		}

		virtual void onAngleChanged(MeasureAngleHandler* sender, double angle)
		{
			oepMeasureAngleHandler^ handle = oepHandleMapManager::getHandle<oepMeasureAngleHandler>(sender);
			if (handle == nullptr)
				return;
			handle->Angle = angle;
		}
	};
}

oepMeasureAngleHandler::oepMeasureAngleHandler() :_angle(0.0)
{
}

void oepMeasureAngleHandler::bind(osgEarth::MapNode* pMapNode)
{
	MeasureAngleHandler* mth = new MeasureAngleHandler(pMapNode);
	mth->addEventHandler(new MeasureAngleToolCallback());
	setRef(mth);
	oepHandleMapManager::registerHandle(mth, this);

	mth->setIntersectionMask(0x1);

	_nodemask = pMapNode->getNodeMask();
	pMapNode->setNodeMask(0x1);
}

void oepMeasureAngleHandler::unbind(osgEarth::MapNode* pMapNode)
{
	MeasureAngleHandler* handle = as<MeasureAngleHandler>();
	if (!handle)
		return;

	if (handle->getMapNode())
	{
		handle->getMapNode()->setNodeMask(_nodemask);
	}
	handle->setMapNode(NULL);
	oepHandleMapManager::unRegisterHandle(handle);
}

double oepMeasureAngleHandler::Angle::get()
{
	return _angle;
}

void oepMeasureAngleHandler::Angle::set(double a)
{
	_angle = a;
	NotifyChanged("Angle");
}

bool oepMeasureAngleHandler::bGreatCircle::get()
{
	MeasureAngleHandler* handle = as<MeasureAngleHandler>();
	if (!handle)
		return false;
	return handle->getGeoInterpolation() == osgEarth::GEOINTERP_GREAT_CIRCLE;
}

void oepMeasureAngleHandler::bGreatCircle::set(bool b)
{
	MeasureAngleHandler* handle = as<MeasureAngleHandler>();
	if (!handle)
		return;
	if (b)
		handle->setGeoInterpolation(osgEarth::GEOINTERP_GREAT_CIRCLE);
	else
		handle->setGeoInterpolation(osgEarth::GEOINTERP_RHUMB_LINE);
	NotifyChanged("bGreatCircle");
}
