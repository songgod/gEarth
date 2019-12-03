#include "stdafx.h"
#include "oepMeasureAreaHandler.h"
#include "oepHandleMapManager.h"
#include "MeasureAreaHandler.h"

using namespace gEarthPack;

namespace
{
	class MeasureAreaToolCallback : public MeasureAreaHandler::MeasureAreaResultHandler
	{
	public:
		MeasureAreaToolCallback()
		{
		}

		virtual void onAreaChanged(MeasureAreaHandler* sender, double area)
		{
			oepMeasureAreaHandler^ handle = oepHandleMapManager::getHandle<oepMeasureAreaHandler>(sender);
			if (handle == nullptr)
				return;
			handle->Area = area;
		}
	};
}


oepMeasureAreaHandler::oepMeasureAreaHandler():_area(0.0)
{

}

void oepMeasureAreaHandler::bind(osgEarth::MapNode* pMapNode)
{
	MeasureAreaHandler* mth = new MeasureAreaHandler(pMapNode);
	mth->getResHandlers().push_back(new MeasureAreaToolCallback());
	bind(mth);
	oepHandleMapManager::registerHandle(mth, this);

	mth->setIntersectionMask(0x1);

	_nodemask = pMapNode->getNodeMask();
	pMapNode->setNodeMask(0x1);
	//Style style = mth->getLineStyle();
	//style.getOrCreate<LineSymbol>()->stroke()->width() = 1.0f;
	//style.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
	//style.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_GPU;
	//mth->setLineStyle(style);
}

void oepMeasureAreaHandler::unbind(osgEarth::MapNode* pMapNode)
{
	MeasureAreaHandler* handle = as<MeasureAreaHandler>();
	if (!handle)
		return;

	if (handle->getMapNode())
	{
		handle->getMapNode()->setNodeMask(_nodemask);
	}
	handle->setMapNode(NULL);
	oepHandleMapManager::unRegisterHandle(handle);
}

double oepMeasureAreaHandler::Area::get()
{
	return _area;
}

void oepMeasureAreaHandler::Area::set(double a)
{
	_area = a;
	NotifyChanged("Area");
}

bool oepMeasureAreaHandler::bGreatCircle::get()
{
	MeasureAreaHandler* handle = as<MeasureAreaHandler>();
	if (!handle)
		return false;
	return handle->getGeoInterpolation() == osgEarth::GEOINTERP_GREAT_CIRCLE;
}

void oepMeasureAreaHandler::bGreatCircle::set(bool b)
{
	MeasureAreaHandler* handle = as<MeasureAreaHandler>();
	if (!handle)
		return;
	if (b)
		handle->setGeoInterpolation(osgEarth::GEOINTERP_GREAT_CIRCLE);
	else
		handle->setGeoInterpolation(osgEarth::GEOINTERP_RHUMB_LINE);
	NotifyChanged("bGreatCircle");
}

bool gEarthPack::oepMeasureAreaHandler::bSurface::get()
{
	MeasureAreaHandler* handle = as<MeasureAreaHandler>();
	if (!handle)
		return false;
	return handle->getSurface();
}

void gEarthPack::oepMeasureAreaHandler::bSurface::set(bool b)
{
	MeasureAreaHandler* handle = as<MeasureAreaHandler>();
	if (!handle || handle->getSurface()==b)
		return;
	handle->setSurface(b);
	NotifyChanged("bSurface");
}
