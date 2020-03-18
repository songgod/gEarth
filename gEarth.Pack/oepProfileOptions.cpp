#include "stdafx.h"
#include "oepProfileOptions.h"

using namespace gEarthPack;


oepProfileOptions::oepProfileOptions()
{
	bind(new osgEarth::ProfileOptions(),true);
}

void gEarthPack::oepProfileOptions::binded()
{
	_bounds = gcnew oepBounds();
	_bounds->bind(as<osgEarth::ProfileOptions>()->bounds(), false);
}

void gEarthPack::oepProfileOptions::unbinded()
{
	_bounds->unbind();
}

String^ oepProfileOptions::NamedProfile::get()
{
	return Str2Cli(as<osgEarth::ProfileOptions>()->namedProfile().value());
}

void oepProfileOptions::NamedProfile::set(String^ v)
{
	as<osgEarth::ProfileOptions>()->namedProfile() = Str2Std(v);
	NotifyChanged("NamedProfile");
}

String^ oepProfileOptions::SrsString::get()
{
	return Str2Cli(as<osgEarth::ProfileOptions>()->srsString().value());
}

void oepProfileOptions::SrsString::set(String^ v)
{
	as<osgEarth::ProfileOptions>()->srsString() = Str2Std(v);
	NotifyChanged("SrsString");
}

String^ oepProfileOptions::VsrsString::get()
{
	return Str2Cli(as<osgEarth::ProfileOptions>()->vsrsString().value());
}

void oepProfileOptions::VsrsString::set(String^ v)
{
	as<osgEarth::ProfileOptions>()->vsrsString() = Str2Std(v);
	NotifyChanged("VsrsString");
}

oepBounds^ oepProfileOptions::Bounds::get()
{	
	return _bounds;
}

void oepProfileOptions::Bounds::set(oepBounds^ p)
{
	osgEarth::ProfileOptions* to = as<osgEarth::ProfileOptions>();
	if (to != NULL && p!=nullptr)
	{
		to->bounds() = *(p->as<osgEarth::Bounds>());
	}
	NotifyChanged("Bounds");
}

int oepProfileOptions::NumTilesWideAtLod0::get()
{
	return as<osgEarth::ProfileOptions>()->numTilesWideAtLod0().value();
}

void oepProfileOptions::NumTilesWideAtLod0::set(int p)
{
	as<osgEarth::ProfileOptions>()->numTilesWideAtLod0() = p;
	NotifyChanged("NumTilesWideAtLod0");
}

int oepProfileOptions::NumTilesHighAtLod0::get()
{
	return as<osgEarth::ProfileOptions>()->numTilesHighAtLod0().value();
}

void oepProfileOptions::NumTilesHighAtLod0::set(int p)
{
	as<osgEarth::ProfileOptions>()->numTilesHighAtLod0() = p;
	NotifyChanged("NumTilesHighAtLod0");
}
