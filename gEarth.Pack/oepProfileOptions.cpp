#include "stdafx.h"
#include "oepProfileOptions.h"

using namespace gEarthPack;
using namespace msclr::interop;

oepProfileOptions::oepProfileOptions()
{
	setVal(new osgEarth::ProfileOptions());
}

String^ oepProfileOptions::NamedProfile::get()
{
	return marshal_as<String^>(as<osgEarth::ProfileOptions>()->namedProfile().value());
}

void oepProfileOptions::NamedProfile::set(String^ v)
{
	as<osgEarth::ProfileOptions>()->namedProfile() = marshal_as<std::string>(v);
	NotifyChanged("NamedProfile");
}

String^ oepProfileOptions::SrsString::get()
{
	return marshal_as<String^>(as<osgEarth::ProfileOptions>()->srsString().value());
}

void oepProfileOptions::SrsString::set(String^ v)
{
	as<osgEarth::ProfileOptions>()->srsString() = marshal_as<std::string>(v);
	NotifyChanged("SrsString");
}

String^ oepProfileOptions::VsrsString::get()
{
	return marshal_as<String^>(as<osgEarth::ProfileOptions>()->vsrsString().value());
}

void oepProfileOptions::VsrsString::set(String^ v)
{
	as<osgEarth::ProfileOptions>()->vsrsString() = marshal_as<std::string>(v);
	NotifyChanged("VsrsString");
}

oepBounds^ oepProfileOptions::Bounds::get()
{
	return _bounds;
}

void oepProfileOptions::Bounds::set(oepBounds^ p)
{
	_bounds = p;
	if(p!=nullptr)
		as<osgEarth::ProfileOptions>()->bounds() = *(p->val());
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
