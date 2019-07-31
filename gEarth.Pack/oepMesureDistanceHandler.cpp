#include "stdafx.h"
#include "oepMesureDistanceHandler.h"
using namespace System::Collections::Generic;

namespace
{
	ref class MesureHandlerCache
	{
		typedef Dictionary<IntPtr, gEarthPack::oepMesureDistanceHandler^> HandleMap;
	public:
		static MesureHandlerCache()
		{
			_handlemap = gcnew HandleMap();
		}

	public:

		static void registerHandle(gEarthPack::oepMesureDistanceHandler^ oephandle)
		{
			if (oephandle == nullptr)
				return;

			MeasureToolHandler* handle = oephandle->asMesureDistanceHandler();
			if (handle == NULL)
				return;

			_handlemap[IntPtr(handle)] = oephandle;
		}

		static void unRegisterHandle(MeasureToolHandler* handle)
		{
			if (handle == NULL)
				return;


			for each (IntPtr key in _handlemap->Keys)
			{
				if (key.ToPointer() == handle)
				{
					_handlemap->Remove(key);
					break;
				}
			}
		}

		static void unRegisterHandle(gEarthPack::oepMesureDistanceHandler^ oephandle)
		{
			if (oephandle == nullptr)
				return;

			typedef KeyValuePair<IntPtr, gEarthPack::oepMesureDistanceHandler^> HandlePair;
			for each (HandlePair p in _handlemap)
			{
				if (p.Value == oephandle)
				{
					_handlemap->Remove(p.Key);
					break;
				}
			}
		}

		static gEarthPack::oepMesureDistanceHandler^ getHandle(MeasureToolHandler* handle)
		{
			if (handle == NULL)
				return nullptr;


			for each (IntPtr key in _handlemap->Keys)
			{
				if (key.ToPointer() == handle)
				{
					return _handlemap[key];
				}
			}
			return nullptr;
		}

	private:

		static HandleMap^ _handlemap;
	};

	class MeasureDistanceToolCallback : public MeasureToolHandler::MeasureToolEventHandler
	{
	public:
		MeasureDistanceToolCallback()
		{
		}

		virtual void onDistanceChanged(MeasureToolHandler* sender, double distance)
		{
			gEarthPack::oepMesureDistanceHandler^ handle = MesureHandlerCache::getHandle(sender);
			if (handle == nullptr)
				return;
			handle->Distance = distance;
		}
	};
}

gEarthPack::oepMesureDistanceHandler::oepMesureDistanceHandler() : _distance(0.0)
{
	MeasureToolHandler* mth = new MeasureToolHandler(NULL);
	mth->addEventHandler(new MeasureDistanceToolCallback());
	_handle->setValue(mth);
	MesureHandlerCache::registerHandle(this);
}

MeasureToolHandler* gEarthPack::oepMesureDistanceHandler::asMesureDistanceHandler()
{
	return dynamic_cast<MeasureToolHandler*>(_handle->getValue());
}

void gEarthPack::oepMesureDistanceHandler::setMapNode(osgEarth::MapNode* pMapNode)
{
	MeasureToolHandler* handle = asMesureDistanceHandler();
	if (!handle)
		return;

	
	handle->setMapNode(pMapNode);
	handle->setIntersectionMask(0x1);
	if (pMapNode)
	{
		_nodemask = pMapNode->getNodeMask();
		pMapNode->setNodeMask(0x1);
		Style style = handle->getLineStyle();
		style.getOrCreate<LineSymbol>()->stroke()->color() = Color::Red;
		style.getOrCreate<LineSymbol>()->stroke()->width() = 4.0f;
		handle->setLineStyle(style);
	}
}

osgEarth::MapNode* gEarthPack::oepMesureDistanceHandler::getMapNode()
{
	MeasureToolHandler* handle = asMesureDistanceHandler();
	if (!handle)
		return NULL;
	return handle->getMapNode();
}

void gEarthPack::oepMesureDistanceHandler::quit()
{
	MeasureToolHandler* handle = asMesureDistanceHandler();
	if (!handle)
		return;
	handle->setMapNode(NULL);
	if (getMapNode())
	{
		getMapNode()->setNodeMask(_nodemask);
	}
	MesureHandlerCache::unRegisterHandle(this);
}

double gEarthPack::oepMesureDistanceHandler::Distance::get()
{
	return _distance;
}

void gEarthPack::oepMesureDistanceHandler::Distance::set(double d)
{
	_distance = d;
	NotifyChanged("Distance");
}

bool gEarthPack::oepMesureDistanceHandler::bPath::get()
{
	MeasureToolHandler* handle = asMesureDistanceHandler();
	if (!handle)
		return false;

	return handle->getIsPath();
}

void gEarthPack::oepMesureDistanceHandler::bPath::set(bool b)
{
	MeasureToolHandler* handle = asMesureDistanceHandler();
	if (!handle)
		return;

	handle->setIsPath(b);
	NotifyChanged("bPath");
}

bool gEarthPack::oepMesureDistanceHandler::bGreatCircle::get()
{
	MeasureToolHandler* handle = asMesureDistanceHandler();
	if (!handle)
		return false;

	return handle->getGeoInterpolation() == osgEarth::GEOINTERP_GREAT_CIRCLE;
}

void gEarthPack::oepMesureDistanceHandler::bGreatCircle::set(bool b)
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
