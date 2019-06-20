#include "stdafx.h"
#include "oepLayerFactory.h"
#include "oepImageLayer.h"
#include "oepElevationLayer.h"
#include "oepUnknownLayer.h"
#include <osgEarth/ImageLayer>
#include <osgEarth/ElevationLayer>

using namespace gEarthPack;

namespace gEarthPack
{
	private ref class oepImageLayerCreator : ILayerCreator
	{
	public:
		virtual String^ supportType()
		{
			return "image";
		}

		virtual oepLayer ^ createLayer(IntPtr param)
		{
			osgEarth::ImageLayer* pImageLayer = (osgEarth::ImageLayer*)param.ToPointer();
			return gcnew oepImageLayer(pImageLayer);
		}
	};

	private ref class oepElevationLayerCreator : ILayerCreator
	{
	public:
		virtual String^ supportType()
		{
			return "elevation";
		}
		virtual oepLayer ^ createLayer(IntPtr param)
		{
			osgEarth::ElevationLayer* pElevationLayer = (osgEarth::ElevationLayer*)param.ToPointer();
			return gcnew oepElevationLayer(pElevationLayer);
		}
	};

	private ref class oepUnkownLayerCreator : ILayerCreator
	{
	public:
		virtual String^ supportType()
		{
			return "unknown";
		}
		virtual oepLayer ^ createLayer(IntPtr param)
		{
			osgEarth::Layer* pLayer = (osgEarth::Layer*)param.ToPointer();
			return gcnew oepUnknownLayer(pLayer);
		}
	};
}


static oepLayerFactory::oepLayerFactory()
{
	_creatorcache = gcnew Dictionary<String^, ILayerCreator^>();
	registerCreator(gcnew oepImageLayerCreator());
	registerCreator(gcnew oepElevationLayerCreator());
	registerCreator(gcnew oepUnkownLayerCreator());
}

void gEarthPack::oepLayerFactory::registerCreator(ILayerCreator^ creator)
{
	if (creator == nullptr)
		return;
	_creatorcache[creator->supportType()] = creator;
}

void gEarthPack::oepLayerFactory::unregisterCreator(String^ type)
{
	_creatorcache->Remove(type);
}

gEarthPack::oepLayer^ gEarthPack::oepLayerFactory::creatorLayer(String^ type, IntPtr param)
{
	if (_creatorcache->ContainsKey(type))
		return _creatorcache[type]->createLayer(param);

	return _creatorcache["unknown"]->createLayer(param);
}
