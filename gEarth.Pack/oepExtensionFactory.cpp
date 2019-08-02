#include "stdafx.h"
#include "oepExtensionFactory.h"
#include "oepSimpleSkyExtension.h"
#include "oepViewpointsExtension.h"
#include <osgEarthDrivers/sky_simple/SimpleSkyOptions>
#include <osgEarthDrivers/viewpoints/ViewpointsOptions>
#include "oepAnimationPathExtension.h"

using namespace gEarthPack;

namespace gEarthPack
{
	osgEarth::Extension* createSpecialExtension(const osgEarth::Config& conf)
	{
		// special support for the default sky extension:
		if (conf.key() == "sky" && !conf.hasValue("driver"))
			return osgEarth::Extension::create("sky_simple", conf);

		if (conf.key() == "ocean" && !conf.hasValue("driver"))
			return osgEarth::Extension::create("ocean_simple", conf);

		return 0L;
	}

	private ref class oepSimpleSkyCreator : IoepExtensionCreator
	{
	public:
		virtual String^ supportType()
		{
			return "simple_sky";
		}

		virtual oepExtension ^ createExtenson(IntPtr param)
		{
			osgEarth::Extension* extension = (osgEarth::Extension*)(param.ToPointer());
			if (!extension) throw gcnew Exception("Invalid simple sky extension");
			return gcnew oepSimpleSkyExtension(extension);
		}
	};

	private ref class oepViewpointsExtensionCreator : IoepExtensionCreator
	{
	public:
		virtual String^ supportType()
		{
			return "viewpoints";
		}

		virtual oepExtension ^ createExtenson(IntPtr param)
		{
			osgEarth::Extension* extension = (osgEarth::Extension*)(param.ToPointer());
			if (!extension) throw gcnew Exception("Invalid viewpoints extension");
			return gcnew oepViewpointsExtension(extension);
		}
	};

	private ref class oepAnimationPathExtensionCreator : IoepExtensionCreator
	{
	public:
		virtual String^ supportType()
		{
			return "animationpath";
		}

		virtual oepExtension ^ createExtenson(IntPtr param)
		{
			osgEarth::Extension* extension = (osgEarth::Extension*)(param.ToPointer());
			if (!extension) throw gcnew Exception("Invalid viewpoints extension");
			return gcnew oepAnimationPathExtension(extension);
		}
	};
}


static oepExtensionFactory::oepExtensionFactory()
{
	_creatorcache = gcnew Dictionary<String^, IoepExtensionCreator^>();
	registerCreator(gcnew oepSimpleSkyCreator());
	registerCreator(gcnew oepViewpointsExtensionCreator());
	registerCreator(gcnew oepAnimationPathExtensionCreator());
}

void oepExtensionFactory::registerCreator(IoepExtensionCreator^ creator)
{
	if (creator == nullptr)
		return;
	_creatorcache[creator->supportType()] = creator;
}

void oepExtensionFactory::unregisterCreator(String^ type)
{
	_creatorcache->Remove(type);
}

oepExtension^ oepExtensionFactory::creatorExtenson(String^ type, IntPtr param)
{
	if (_creatorcache->ContainsKey(type))
		return _creatorcache[type]->createExtenson(param);

	return nullptr;
}

osgEarth::Extension* oepExtensionFactory::createoeExtension(const osgEarth::Config& config)
{
	std::string name = config.key();
	osgEarth::Extension* extension = osgEarth::Extension::create(name, config);
	if (!extension)
	{
		name = config.key() + "_" + config.value("driver");
		extension = osgEarth::Extension::create(name, config);

		if (!extension)
			extension = createSpecialExtension(config);
	}
	return extension;
}

