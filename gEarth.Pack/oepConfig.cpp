#include "stdafx.h"
#include "oepConfig.h"

using namespace gEarthPack;
using namespace msclr::interop;

oepConfig::oepConfig()
{
	bind(new osgEarth::Config(),true);
}

void oepConfig::binded()
{
	_children = gcnew oepConfigSet();
	_children->bind(&(as<osgEarth::Config>()->children()), false);
}

void oepConfig::unbinded()
{
	_children->unbind();
}

String^ oepConfig::Referrer::get()
{
	return marshal_as<String^>(as<osgEarth::Config>()->referrer());
}

void oepConfig::Referrer::set(String^ p)
{
	as<osgEarth::Config>()->setReferrer(marshal_as<std::string>(p));
	NotifyChanged("Referrer");
}

bool oepConfig::IsLocation::get()
{
	return as<osgEarth::Config>()->isLocation();
}

void oepConfig::IsLocation::set(bool p)
{
	as<osgEarth::Config>()->setIsLocation(p);
	NotifyChanged("IsLocation");
}

String^ oepConfig::ExternalRef::get()
{
	return marshal_as<String^>(as<osgEarth::Config>()->externalRef());
}

void oepConfig::ExternalRef::set(String^ p)
{
	as<osgEarth::Config>()->setExternalRef(marshal_as<std::string>(p));
	NotifyChanged("ExternalRef");
}

String^ oepConfig::Joson::get()
{
	return marshal_as<String^>(as<osgEarth::Config>()->toJSON());
}

void oepConfig::Joson::set(String^ p)
{
	as<osgEarth::Config>()->fromJSON(marshal_as<std::string>(p));
	NotifyChanged("Joson");
}

bool oepConfig::IsEmpty::get()
{
	return as<osgEarth::Config>()->empty();
}

bool gEarthPack::oepConfig::IsSimple::get()
{
	return as<osgEarth::Config>()->isSimple();
}

String^ oepConfig::Key::get()
{
	return marshal_as<String^>(as<osgEarth::Config>()->key());
}

void oepConfig::Key::set(String^ p)
{
	as<osgEarth::Config>()->key() = marshal_as<std::string>(p);
	NotifyChanged("Key");
}

String^ oepConfig::Value::get()
{
	return marshal_as<String^>(as<osgEarth::Config>()->value());
}

oepConfigSet^ oepConfig::Children::get()
{
	return _children;
}

void oepConfig::Children::set(oepConfigSet^ p)
{
	_children = p;

	osgEarth::ConfigSet& configset = as<osgEarth::Config>()->children();
	_children->getVal(configset);
	_children->bind(&configset,false);
	NotifyChanged("Children");
}
