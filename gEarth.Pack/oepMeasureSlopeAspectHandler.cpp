#include "stdafx.h"
#include "oepMeasureSlopeAspectHandler.h"
#include "MeasureSlopeAspectHandler.h"
#include "oepHandleMapManager.h"

using namespace gEarthPack;

namespace gEarthPack
{
	class MeasureSlopeAspectCallback : public MeasureSlopeAspectHandler::MeasureSlopeAspectEventHandler
	{
	public:
		MeasureSlopeAspectCallback()
		{
		}

		virtual void onSlopeAspectChanged(MeasureSlopeAspectHandler* sender, double slope, double aspect, osg::Vec3 point)
		{
			oepMeasureSlopeAspectHandler^ handle = oepHandleMapManager::getHandle<oepMeasureSlopeAspectHandler>(sender);
			if (handle == nullptr)
				return;
			handle->Slope = slope;
			handle->Aspect = aspect;
			handle->Point = oepVec3f(point.x(), point.y(), point.z());
		}
	};
}

oepMeasureSlopeAspectHandler::oepMeasureSlopeAspectHandler():_slope(0.f),_aspect(0.f)
{
}

void oepMeasureSlopeAspectHandler::bind(osgEarth::MapNode* pMapNode)
{
	MeasureSlopeAspectHandler* mth = new MeasureSlopeAspectHandler();
	mth->setMapNode(pMapNode);
	mth->addEventHandler(new MeasureSlopeAspectCallback());
	bind(mth);
	oepHandleMapManager::registerHandle(mth, this);

	mth->setIntersectionMask(0x1);

	_nodemask = pMapNode->getNodeMask();
	pMapNode->setNodeMask(0x1);
}

void oepMeasureSlopeAspectHandler::unbind(osgEarth::MapNode* pMapNode)
{
	MeasureSlopeAspectHandler* handle = as<MeasureSlopeAspectHandler>();
	if (!handle)
		return;

	if (handle->getMapNode())
	{
		handle->getMapNode()->setNodeMask(_nodemask);
	}
	handle->setMapNode(NULL);
	oepHandleMapManager::unRegisterHandle(handle);
}

double oepMeasureSlopeAspectHandler::Slope::get()
{
	return _slope;
}

void oepMeasureSlopeAspectHandler::Slope::set(double a)
{
	_slope = a;
	NotifyChanged("Slope");
}

double oepMeasureSlopeAspectHandler::Aspect::get()
{
	return _aspect;
}

void oepMeasureSlopeAspectHandler::Aspect::set(double b)
{
	_aspect = b;
	NotifyChanged("Aspect");
}

oepVec3f oepMeasureSlopeAspectHandler::Point::get()
{
	return _point;
}

void oepMeasureSlopeAspectHandler::Point::set(oepVec3f p)
{
	_point = p;
	NotifyChanged("Point");
}
