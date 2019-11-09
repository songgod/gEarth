#include "stdafx.h"
#include "oepMeasureVolumeHander.h"
#include "MeasureVolumeHandler.h"
#include "oepHandleMapManager.h"

using namespace gEarthPack;

namespace
{
	class MeasureVolumeCallback : public MeasureVolumeHandler::MeasureVolumeResultHandler
	{
	public:
		MeasureVolumeCallback()
		{
		}

		virtual void onVolumeChanged(MeasureVolumeHandler* sender, double volume)
		{
			oepMeasureVolumeHander^ handle = oepHandleMapManager::getHandle<oepMeasureVolumeHander>(sender);
			if (handle == nullptr)
				return;
			handle->Volume = volume;
		}
	};
}

oepMeasureVolumeHander::oepMeasureVolumeHander()
{
}

void oepMeasureVolumeHander::bind(osgEarth::MapNode* pMapNode)
{
	MeasureVolumeHandler* mth = new MeasureVolumeHandler(pMapNode);
	mth->getResHandlers().push_back(new MeasureVolumeCallback());
	_handle->setValue(mth);
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

void oepMeasureVolumeHander::unbind(osgEarth::MapNode* pMapNode)
{
	MeasureVolumeHandler* handle = as<MeasureVolumeHandler>();
	if (!handle)
		return;

	if (handle->getMapNode())
	{
		handle->getMapNode()->setNodeMask(_nodemask);
	}
	handle->setMapNode(NULL);
	oepHandleMapManager::unRegisterHandle(handle);
}

double oepMeasureVolumeHander::Volume::get()
{
	return _volume;
}

void oepMeasureVolumeHander::Volume::set(double v)
{
	_volume = v;
	NotifyChanged("Volume");
}

bool oepMeasureVolumeHander::bGreatCircle::get()
{
	MeasureVolumeHandler* handle = as<MeasureVolumeHandler>();
	if (!handle)
		return false;
	return handle->getGeoInterpolation() == osgEarth::GEOINTERP_GREAT_CIRCLE;
}

void oepMeasureVolumeHander::bGreatCircle::set(bool b)
{
	MeasureVolumeHandler* handle = as<MeasureVolumeHandler>();
	if (!handle)
		return;
	if (b)
		handle->setGeoInterpolation(osgEarth::GEOINTERP_GREAT_CIRCLE);
	else
		handle->setGeoInterpolation(osgEarth::GEOINTERP_RHUMB_LINE);
	NotifyChanged("bGreatCircle");
}

double oepMeasureVolumeHander::Deep::get()
{
	MeasureVolumeHandler* handle = as<MeasureVolumeHandler>();
	if (!handle)
		return 0.0;
	return handle->getDeep();
}

void oepMeasureVolumeHander::Deep::set(double v)
{
	MeasureVolumeHandler* handle = as<MeasureVolumeHandler>();
	if (!handle || osg::equivalent(v,handle->getDeep()))
		return;
	handle->setDeep(v);
	NotifyChanged("Deep");
}
