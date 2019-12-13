#include "stdafx.h"
#include "oepDriverConfigOptions.h"

using namespace gEarthPack;


oepDriverConfigOptions::oepDriverConfigOptions()
{
}

String^ oepDriverConfigOptions::Driver::get()
{
	return Str2Cli(as<osgEarth::DriverConfigOptions>()->getDriver());
}

void oepDriverConfigOptions::Driver::set(String^ p)
{
	as<osgEarth::Features::DriverConfigOptions>()->setDriver(Str2Std(p));
	NotifyChanged("Name");
}
