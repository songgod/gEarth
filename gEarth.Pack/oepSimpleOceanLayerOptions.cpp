#include "stdafx.h"
#include "oepSimpleOceanLayerOptions.h"

using namespace msclr::interop;
using namespace gEarthPack;
oepSimpleOceanLayerOptions::oepSimpleOceanLayerOptions()
{
	bind(new osgEarth::Util::SimpleOceanLayerOptions(),true);
}

oepVec4f oepSimpleOceanLayerOptions::Color::get()
{
	osgEarth::Color c = as<osgEarth::Util::SimpleOceanLayerOptions>()->color().value();
	return oepVec4f(c.r(), c.g(), c.b(), c.a());
}

void oepSimpleOceanLayerOptions::Color::set(oepVec4f v)
{
	osgEarth::Color c(v.x, v.y, v.z, v.a);
	as<osgEarth::Util::SimpleOceanLayerOptions>()->color() = c;
	NotifyChanged("Color");
}

float oepSimpleOceanLayerOptions::MaxAltitude::get()
{
	return as<osgEarth::Util::SimpleOceanLayerOptions>()->maxAltitude().value();
}

void oepSimpleOceanLayerOptions::MaxAltitude::set(float v)
{
	as<osgEarth::Util::SimpleOceanLayerOptions>()->maxAltitude() = v;
	NotifyChanged("MaxAltitude");
}

String^ oepSimpleOceanLayerOptions::MaskLayer::get()
{
	return marshal_as<String^>(as<osgEarth::Util::SimpleOceanLayerOptions>()->maskLayer().value());
}

void oepSimpleOceanLayerOptions::MaskLayer::set(String^ v)
{
	as<osgEarth::Util::SimpleOceanLayerOptions>()->maskLayer() = marshal_as<std::string>(v);
	NotifyChanged("MaskLayer");
}

bool oepSimpleOceanLayerOptions::UseBathymetry::get()
{
	return as<osgEarth::Util::SimpleOceanLayerOptions>()->useBathymetry().value();
}

void oepSimpleOceanLayerOptions::UseBathymetry::set(bool b)
{
	as<osgEarth::Util::SimpleOceanLayerOptions>()->useBathymetry() = b;
	NotifyChanged("UseBathymetry");
}

String^ oepSimpleOceanLayerOptions::TextureUrl::get()
{
	return marshal_as<String^>(as<osgEarth::Util::SimpleOceanLayerOptions>()->texture().value().full());
}

void oepSimpleOceanLayerOptions::TextureUrl::set(String^ url)
{
	as<osgEarth::Util::SimpleOceanLayerOptions>()->texture()= marshal_as<std::string>(url);
	NotifyChanged("TextureUrl");
}

unsigned oepSimpleOceanLayerOptions::TextureLOD::get()
{
	return as<osgEarth::Util::SimpleOceanLayerOptions>()->textureLOD().value();
}

void oepSimpleOceanLayerOptions::TextureLOD::set(unsigned v)
{
	as<osgEarth::Util::SimpleOceanLayerOptions>()->textureLOD() = v;
	NotifyChanged("TextureLOD");
}
