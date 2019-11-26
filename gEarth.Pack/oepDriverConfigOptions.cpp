#include "stdafx.h"
#include "oepDriverConfigOptions.h"

using namespace gEarthPack;
using namespace msclr::interop;

oepDriverConfigOptions::oepDriverConfigOptions()
{
}

String^ oepDriverConfigOptions::Driver::get()
{
	return marshal_as<String^>(as<osgEarth::DriverConfigOptions>()->getDriver());
}

void oepDriverConfigOptions::Driver::set(String^ p)
{
	as<osgEarth::Features::DriverConfigOptions>()->setDriver(marshal_as<std::string>(p));
	NotifyChanged("Name");
}
