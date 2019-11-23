#include "stdafx.h"
#include "MeasureProfileHandler.h"
#include "oepMeasureProfileHandler.h"
#include "oepHandleMapManager.h"

using namespace gEarthPack;
using namespace osgEarth::Util;

namespace
{
	struct MeasureProfileCallback : public TerrainProfileCalculator::ChangedCallback
	{
	public:
		MeasureProfileCallback(MeasureProfileHandler* handler):_handler(handler)
		{
		}

		virtual void onChanged(const TerrainProfileCalculator* sender)
		{
			oepMeasureProfileHandler^ handle = oepHandleMapManager::getHandle<oepMeasureProfileHandler>(_handler);
			if (handle == nullptr)
				return;
			
			handle->Profiles = nullptr;
			const TerrainProfile& profile = sender->getProfile();
			handle->TotalDistance = profile.getTotalDistance();
			double min = 0.0;
			double max = 0.0;
			profile.getElevationRanges(min, max);
			handle->MinElevation = min;
			handle->MaxElevation = max;
			List<oepVec2f>^ p = gcnew List<oepVec2f>();
			for (unsigned int i = 0; i < profile.getNumElevations(); i++)
			{
				p->Add(oepVec2f(profile.getDistance(i), profile.getElevation(i)));
			}
			handle->Profiles = p;
		}

	private:

		MeasureProfileHandler* _handler;
	};
}

oepMeasureProfileHandler::oepMeasureProfileHandler():_totaldistance(0.0), _minelevation(0.0), _maxelevation(0.0)
{
	
}

void oepMeasureProfileHandler::bind(osgEarth::MapNode* pMapNode)
{
	MeasureProfileHandler* mth = new MeasureProfileHandler(pMapNode);
	mth->getProfileCalculator()->addChangedCallback(new MeasureProfileCallback(mth));
	setRef(mth);
	oepHandleMapManager::registerHandle(mth, this);

	mth->setIntersectionMask(0x1);

	_nodemask = pMapNode->getNodeMask();
	pMapNode->setNodeMask(0x1);
}

void oepMeasureProfileHandler::unbind(osgEarth::MapNode* pMapNode)
{
	MeasureProfileHandler* handle = as<MeasureProfileHandler>();
	if (!handle)
		return;

	if (handle->getMapNode())
	{
		handle->getMapNode()->setNodeMask(_nodemask);
	}
	handle->setMapNode(NULL);
	oepHandleMapManager::unRegisterHandle(handle);
}


double oepMeasureProfileHandler::TotalDistance::get()
{
	return _totaldistance;
}

void oepMeasureProfileHandler::TotalDistance::set(double v)
{
	if (osg::equivalent(_totaldistance, v))
		return;
	_totaldistance = v;
	NotifyChanged("TotalDistance");
}

double oepMeasureProfileHandler::MinElevation::get()
{
	return _minelevation;
}

void oepMeasureProfileHandler::MinElevation::set(double v)
{
	if (osg::equivalent(_minelevation, v))
		return;
	_minelevation = v;
	NotifyChanged("MinElevation");
}

double oepMeasureProfileHandler::MaxElevation::get()
{
	return _maxelevation;
}

void oepMeasureProfileHandler::MaxElevation::set(double v)
{
	if (osg::equivalent(_maxelevation, v))
		return;
	_maxelevation = v;
	NotifyChanged("MaxElevation");
}

List<oepVec2f>^ oepMeasureProfileHandler::Profiles::get()
{
	return _profile;
}

void oepMeasureProfileHandler::Profiles::set(List<oepVec2f>^ v)
{
	_profile = v;
	NotifyChanged("Profiles");
}
