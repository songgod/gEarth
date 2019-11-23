#include "stdafx.h"
#include "oepLayerFactory.h"
#include "oepImageLayer.h"
#include "oepElevationLayer.h"
#include "oepUnknownLayer.h"
#include "oepSimpleOceanLayer.h"
#include "oepFeatureModelLayer.h"
#include "oepModelLayer.h"

using namespace gEarthPack;

namespace gEarthPack
{
	private ref class oepImageLayerCreator : IoepLayerCreator
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

	private ref class oepElevationLayerCreator : IoepLayerCreator
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

	private ref class oepSimpleOceanLayerCreator : IoepLayerCreator
	{
	public:
		virtual String^ supportType()
		{
			return "simple_ocean";
		}
		virtual oepLayer ^ createLayer(IntPtr param)
		{
			osgEarth::Util::SimpleOceanLayer* pOceanLayer = (osgEarth::Util::SimpleOceanLayer*)param.ToPointer();
			return gcnew oepSimpleOceanLayer(pOceanLayer);
		}
	};

	private ref class oepFeatureModelLayerCreator : IoepLayerCreator
	{

	public:
		virtual String^ supportType()
		{
			return "feature_model";
		}


		virtual oepLayer^ createLayer(IntPtr param)
		{
			osgEarth::Features::FeatureModelLayer* pLayer = (osgEarth::Features::FeatureModelLayer*)param.ToPointer();
			return gcnew oepFeatureModelLayer(pLayer);
		}

	};

	private ref class oepModelLayerCreator : IoepLayerCreator
	{

	public:
		virtual String^ supportType()
		{
			return "model";
		}


		virtual oepLayer^ createLayer(IntPtr param)
		{
			osgEarth::ModelLayer* pLayer = (osgEarth::ModelLayer*)param.ToPointer();
			return gcnew oepModelLayer(pLayer);
		}

	};

	private ref class oepUnkownLayerCreator : IoepLayerCreator
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
	_creatorcache = gcnew Dictionary<String^, IoepLayerCreator^>();
	registerCreator(gcnew oepImageLayerCreator());
	registerCreator(gcnew oepElevationLayerCreator());
	registerCreator(gcnew oepSimpleOceanLayerCreator());
	registerCreator(gcnew oepFeatureModelLayerCreator());
	registerCreator(gcnew oepUnkownLayerCreator());
	registerCreator(gcnew oepModelLayerCreator());
}

void oepLayerFactory::registerCreator(IoepLayerCreator^ creator)
{
	if (creator == nullptr)
		return;
	_creatorcache[creator->supportType()] = creator;
}

void oepLayerFactory::unregisterCreator(String^ type)
{
	_creatorcache->Remove(type);
}

oepLayer^ oepLayerFactory::creatorLayer(String^ type, IntPtr param)
{
	if (_creatorcache->ContainsKey(type))
		return _creatorcache[type]->createLayer(param);

	return _creatorcache["unknown"]->createLayer(param);
}
