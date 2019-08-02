#include "stdafx.h"
#include "oepMeasureAreaHandler.h"
#include "HandleMapManager.h"

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
			oepMeasureAreaHandler^ handle = HandleMapManager::getHandle<oepMeasureAreaHandler>(sender);
			if (handle == nullptr)
				return;
			handle->Area = area;
		}
	};
}


oepMeasureAreaHandler::oepMeasureAreaHandler():_area(0.0)
{

}

MeasureAreaHandler* oepMeasureAreaHandler::asMesureAreaHandler()
{
	return dynamic_cast<MeasureAreaHandler*>(_handle->getValue());
}

void oepMeasureAreaHandler::bind(osgEarth::MapNode* pMapNode)
{
	MeasureAreaHandler* mth = new MeasureAreaHandler(pMapNode);
	mth->getResHandlers().push_back(new MeasureAreaToolCallback());
	_handle->setValue(mth);
	HandleMapManager::registerHandle(mth, this);

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
	MeasureAreaHandler* handle = asMesureAreaHandler();
	if (!handle)
		return;

	if (handle->getMapNode())
	{
		handle->getMapNode()->setNodeMask(_nodemask);
	}
	handle->setMapNode(NULL);
	HandleMapManager::unRegisterHandle(handle);
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

bool gEarthPack::oepMeasureAreaHandler::bGreatCircle::get()
{
	MeasureAreaHandler* handle = asMesureAreaHandler();
	if (!handle)
		return false;
	return handle->getGeoInterpolation() == osgEarth::GEOINTERP_GREAT_CIRCLE;
}

void gEarthPack::oepMeasureAreaHandler::bGreatCircle::set(bool b)
{
	MeasureAreaHandler* handle = asMesureAreaHandler();
	if (!handle)
		return;
	if (b)
		handle->setGeoInterpolation(osgEarth::GEOINTERP_GREAT_CIRCLE);
	else
		handle->setGeoInterpolation(osgEarth::GEOINTERP_RHUMB_LINE);
	NotifyChanged("bGreatCircle");
}
