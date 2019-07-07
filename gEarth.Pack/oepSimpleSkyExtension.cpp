#include "stdafx.h"
#include "oepSimpleSkyExtension.h"
#include "oepExtensionFactory.h"

gEarthPack::oepSimpleSkyExtension::oepSimpleSkyExtension():_bNotifyVisible(true)
{
	osgEarth::SimpleSky::SimpleSkyOptions options;
	osgEarth::Config conf = options.getConfig();
	osgEarth::Extension* extension = oepExtensionFactory::createoeExtension(conf);
	if (!extension) throw gcnew Exception("Invalid simple sky extension");
	_handle = new ExtensionHandle(extension);
}

gEarthPack::oepSimpleSkyExtension::oepSimpleSkyExtension(osgEarth::Extension* ext) :_bNotifyVisible(true)
{
	_handle = new ExtensionHandle(ext);
}

osgEarth::Util::SkyNode* gEarthPack::oepSimpleSkyExtension::getoeSkyNode()
{
	if (!_handle || !_handle->getValue())
		return NULL;
	return dynamic_cast<osgEarth::Util::SkyNode*>(_handle->getValue()->getUserData());
}

osgEarth::SimpleSky::SimpleSkyOptions* gEarthPack::oepSimpleSkyExtension::getoeSimpleSkyOptions()
{
	if (!_handle)
		return NULL;

	return dynamic_cast<osgEarth::SimpleSky::SimpleSkyOptions*>(_handle->getValue());
}

int gEarthPack::oepSimpleSkyExtension::DataYear::get()
{
	osgEarth::Util::SkyNode* sn = getoeSkyNode();
	if (sn)
	{
		osgEarth::DateTime t = sn->getDateTime();
		return t.year();
	}
	return 0;
}

void gEarthPack::oepSimpleSkyExtension::DataYear::set(int v)
{
	osgEarth::Util::SkyNode* sn = getoeSkyNode();
	if (sn)
	{
		osgEarth::DateTime t = sn->getDateTime();
		osgEarth::DateTime tn(v, t.month(), t.day(), t.hours());
		sn->setDateTime(tn);
		NotifyChanged("DataYear");
	}
}

int gEarthPack::oepSimpleSkyExtension::DataMonth::get()
{
	osgEarth::Util::SkyNode* sn = getoeSkyNode();
	if (sn)
	{
		osgEarth::DateTime t = sn->getDateTime();
		return t.month();
	}
	return 0;
}

void gEarthPack::oepSimpleSkyExtension::DataMonth::set(int v)
{
	osgEarth::Util::SkyNode* sn = getoeSkyNode();
	if (sn)
	{
		osgEarth::DateTime t = sn->getDateTime();
		osgEarth::DateTime tn(t.year(), v, t.day(), t.hours());
		sn->setDateTime(tn);
		NotifyChanged("DataMonth");
	}
}

int gEarthPack::oepSimpleSkyExtension::DataDay::get()
{
	osgEarth::Util::SkyNode* sn = getoeSkyNode();
	if (sn)
	{
		osgEarth::DateTime t = sn->getDateTime();
		return t.day();
	}
	return 0;
}

void gEarthPack::oepSimpleSkyExtension::DataDay::set(int v)
{
	osgEarth::Util::SkyNode* sn = getoeSkyNode();
	if (sn)
	{
		osgEarth::DateTime t = sn->getDateTime();
		osgEarth::DateTime tn(t.year(), t.month(), v, t.hours());
		sn->setDateTime(tn);
		NotifyChanged("DataDay");
	}
}

double gEarthPack::oepSimpleSkyExtension::DataHours::get()
{
	osgEarth::Util::SkyNode* sn = getoeSkyNode();
	if (sn)
	{
		osgEarth::DateTime t = sn->getDateTime();
		return t.hours();
	}
	return 0.0;
}

void gEarthPack::oepSimpleSkyExtension::DataHours::set(double v)
{
	osgEarth::Util::SkyNode* sn = getoeSkyNode();
	if (sn)
	{
		osgEarth::DateTime t = sn->getDateTime();
		osgEarth::DateTime tn(t.year(), t.month(), t.day(),v);
		sn->setDateTime(tn);
		NotifyChanged("DataHours");
	}
}

bool gEarthPack::oepSimpleSkyExtension::SunVisible::get()
{
	osgEarth::SimpleSky::SimpleSkyOptions* so = getoeSimpleSkyOptions();
	if (so)
		return so->sunVisible().value();
	return false;
}

void gEarthPack::oepSimpleSkyExtension::SunVisible::set(bool b)
{
	osgEarth::Util::SkyNode* sn = getoeSkyNode();
	osgEarth::SimpleSky::SimpleSkyOptions* so = getoeSimpleSkyOptions();
	if (sn) sn->setSunVisible(b);
	if (so) so->sunVisible() = b;
	NotifyChanged("SunVisible");
	if(_bNotifyVisible)
		NotifyChanged("Visible");
}

bool gEarthPack::oepSimpleSkyExtension::MoonVisible::get()
{
	osgEarth::SimpleSky::SimpleSkyOptions* so = getoeSimpleSkyOptions();
	if (so)
		return so->moonVisible().value();
	return false;
}

void gEarthPack::oepSimpleSkyExtension::MoonVisible::set(bool b)
{
	osgEarth::Util::SkyNode* sn = getoeSkyNode();
	osgEarth::SimpleSky::SimpleSkyOptions* so = getoeSimpleSkyOptions();
	if (sn) sn->setMoonVisible(b);
	if (so) so->moonVisible() = b;
	NotifyChanged("MoonVisible");
	if (_bNotifyVisible)
		NotifyChanged("Visible");
}

bool gEarthPack::oepSimpleSkyExtension::StarsVisible::get()
{
	osgEarth::SimpleSky::SimpleSkyOptions* so = getoeSimpleSkyOptions();
	if (so)
		return so->starsVisible().value();
	return false;
}

void gEarthPack::oepSimpleSkyExtension::StarsVisible::set(bool b)
{
	osgEarth::Util::SkyNode* sn = getoeSkyNode();
	osgEarth::SimpleSky::SimpleSkyOptions* so = getoeSimpleSkyOptions();
	if (sn) sn->setStarsVisible(b);
	if (so) so->starsVisible() = b;
	NotifyChanged("StarsVisible");
	if (_bNotifyVisible)
		NotifyChanged("Visible");
}

bool gEarthPack::oepSimpleSkyExtension::AtmosphereVisible::get()
{
	osgEarth::SimpleSky::SimpleSkyOptions* so = getoeSimpleSkyOptions();
	if (so)
		return so->atmosphereVisible().value();
	return false;
}

void gEarthPack::oepSimpleSkyExtension::AtmosphereVisible::set(bool b)
{
	osgEarth::Util::SkyNode* sn = getoeSkyNode();
	osgEarth::SimpleSky::SimpleSkyOptions* so = getoeSimpleSkyOptions();
	if (sn) sn->setAtmosphereVisible(b);
	if (so) so->atmosphereVisible() = b;
	NotifyChanged("AtmosphereVisible");
	if (_bNotifyVisible)
		NotifyChanged("Visible");
}

Nullable<Boolean> gEarthPack::oepSimpleSkyExtension::Visible::get()
{
	if (SunVisible && MoonVisible && StarsVisible && AtmosphereVisible)
		return Nullable<Boolean>(true);

	if (!SunVisible && !MoonVisible && !StarsVisible && !AtmosphereVisible)
		return Nullable<Boolean>(false);

	return Nullable<Boolean>();
}

void gEarthPack::oepSimpleSkyExtension::Visible::set(Nullable<Boolean> b)
{
	if (!b.HasValue)
		return;
	_bNotifyVisible = false;

	if (b.Value)
	{
		SunVisible = true;
		MoonVisible = true;
		StarsVisible = true;
		AtmosphereVisible = true;
	}
	else
	{
		SunVisible = false;
		MoonVisible = false;
		StarsVisible = false;
		AtmosphereVisible = false;
	}

	_bNotifyVisible = true;
	NotifyChanged("Visible");
}
