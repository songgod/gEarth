#include "stdafx.h"
#include "oepConfig.h"

using namespace gEarthPack;


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
	return Str2Cli(as<osgEarth::Config>()->referrer());
}

void oepConfig::Referrer::set(String^ p)
{
	as<osgEarth::Config>()->setReferrer(Str2Std(p));
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
	return Str2Cli(as<osgEarth::Config>()->externalRef());
}

void oepConfig::ExternalRef::set(String^ p)
{
	as<osgEarth::Config>()->setExternalRef(Str2Std(p));
	NotifyChanged("ExternalRef");
}

String^ oepConfig::Joson::get()
{
	return Str2Cli(as<osgEarth::Config>()->toJSON());
}

void oepConfig::Joson::set(String^ p)
{
	as<osgEarth::Config>()->fromJSON(Str2Std(p));
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

bool gEarthPack::oepConfig::IsNumber::get()
{
	return as<osgEarth::Config>()->isNumber();
}

String^ oepConfig::Key::get()
{
	return Str2Cli(as<osgEarth::Config>()->key());
}

void oepConfig::Key::set(String^ p)
{
	as<osgEarth::Config>()->key() = Str2Std(p);
	NotifyChanged("Key");
}

String^ oepConfig::StrValue::get()
{
	return Str2Cli(as<osgEarth::Config>()->value());
}

void oepConfig::StrValue::set(String^ p)
{
	as<osgEarth::Config>()->setValue<std::string>(Str2Std(p));
	NotifyChanged("StrValue");
}

bool gEarthPack::oepConfig::BoolValue::get()
{
	return as<osgEarth::Config>()->valueAs<bool>(false);
}

void gEarthPack::oepConfig::BoolValue::set(bool p)
{
	as<osgEarth::Config>()->setValue<bool>(p);
	NotifyChanged("StrValue");
	NotifyChanged("BoolValue");
}

short gEarthPack::oepConfig::ShortValue::get()
{
	return as<osgEarth::Config>()->valueAs<short>(0);
}

void gEarthPack::oepConfig::ShortValue::set(short p)
{
	as<osgEarth::Config>()->setValue<short>(p);
	NotifyChanged("StrValue");
	NotifyChanged("ShortValue");
}

unsigned short gEarthPack::oepConfig::UshortValue::get()
{
	return as<osgEarth::Config>()->valueAs<unsigned short>(0);
}

void gEarthPack::oepConfig::UshortValue::set(unsigned short p)
{
	as<osgEarth::Config>()->setValue<unsigned short>(p);
	NotifyChanged("StrValue");
	NotifyChanged("UshortValue");
}

int gEarthPack::oepConfig::IntValue::get()
{
	return as<osgEarth::Config>()->valueAs<int>(0);
}

void gEarthPack::oepConfig::IntValue::set(int p)
{
	as<osgEarth::Config>()->setValue<int>(p);
	NotifyChanged("StrValue");
	NotifyChanged("IntValue");
}

unsigned int gEarthPack::oepConfig::UintValue::get()
{
	return as<osgEarth::Config>()->valueAs<unsigned int>(0);
}

void gEarthPack::oepConfig::UintValue::set(unsigned int p)
{
	as<osgEarth::Config>()->setValue<unsigned int>(p);
	NotifyChanged("StrValue");
	NotifyChanged("UintValue");
}

long gEarthPack::oepConfig::LongValue::get()
{
	return as<osgEarth::Config>()->valueAs<long>(0);
}

void gEarthPack::oepConfig::LongValue::set(long p)
{
	as<osgEarth::Config>()->setValue<long>(p);
	NotifyChanged("StrValue");
	NotifyChanged("LongValue");
}

unsigned long gEarthPack::oepConfig::UlongValue::get()
{
	return as<osgEarth::Config>()->valueAs<unsigned long>(0);
}

void gEarthPack::oepConfig::UlongValue::set(unsigned long p)
{
	as<osgEarth::Config>()->setValue<unsigned long>(p);
	NotifyChanged("StrValue");
	NotifyChanged("UlongValue");
}

float gEarthPack::oepConfig::FloatValue::get()
{
	return as<osgEarth::Config>()->valueAs<float>(0.0);
}

void gEarthPack::oepConfig::FloatValue::set(float p)
{
	as<osgEarth::Config>()->setValue<float>(p);
	NotifyChanged("StrValue");
	NotifyChanged("FloatValue");
}

double gEarthPack::oepConfig::DoubleValue::get()
{
	return as<osgEarth::Config>()->valueAs<double>(0.0);
}

void gEarthPack::oepConfig::DoubleValue::set(double p)
{
	as<osgEarth::Config>()->setValue<double>(p);
	NotifyChanged("StrValue");
	NotifyChanged("DoubleValue");
}

oepConfigSet^ oepConfig::Children::get()
{
	return _children;
}

void oepConfig::Children::set(oepConfigSet^ p)
{
	osgEarth::Config* to = as<osgEarth::Config>();
	if (to != NULL && p != nullptr)
	{
		to->children() = *(p->Val());
		NotifyChanged("Children");
	}
}