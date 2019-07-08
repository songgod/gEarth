#include "stdafx.h"
#include "oepSimpleOceanLayerOptions.h"
#include <msclr\marshal_cppstd.h>  

using namespace msclr::interop;
using namespace gEarthPack;
oepSimpleOceanLayerOptions::oepSimpleOceanLayerOptions()
{
	_handle = new osgEarth::Util::SimpleOceanLayerOptions();
}

osgEarth::Util::SimpleOceanLayerOptions* gEarthPack::oepSimpleOceanLayerOptions::asoeSimpleOceanLayerOptions()
{
	return dynamic_cast<osgEarth::Util::SimpleOceanLayerOptions*>(_handle);
}

gEarthPack::oepVec4f gEarthPack::oepSimpleOceanLayerOptions::Color::get()
{
	osgEarth::Color c = asoeSimpleOceanLayerOptions()->color().value();
	return oepVec4f(c.r(), c.g(), c.b(), c.a());
}

void gEarthPack::oepSimpleOceanLayerOptions::Color::set(oepVec4f v)
{
	osgEarth::Color c(v.x, v.y, v.z, v.a);
	asoeSimpleOceanLayerOptions()->color() = c;
	NotifyChanged("Color");
}

float gEarthPack::oepSimpleOceanLayerOptions::MaxAltitude::get()
{
	return asoeSimpleOceanLayerOptions()->maxAltitude().value();
}

void gEarthPack::oepSimpleOceanLayerOptions::MaxAltitude::set(float v)
{
	asoeSimpleOceanLayerOptions()->maxAltitude() = v;
	NotifyChanged("MaxAltitude");
}

String^ gEarthPack::oepSimpleOceanLayerOptions::MaskLayer::get()
{
	return marshal_as<String^>(asoeSimpleOceanLayerOptions()->maskLayer().value());
}

void gEarthPack::oepSimpleOceanLayerOptions::MaskLayer::set(String^ v)
{
	asoeSimpleOceanLayerOptions()->maskLayer() = marshal_as<std::string>(v);
	NotifyChanged("MaskLayer");
}

bool gEarthPack::oepSimpleOceanLayerOptions::UseBathymetry::get()
{
	return asoeSimpleOceanLayerOptions()->useBathymetry().value();
}

void gEarthPack::oepSimpleOceanLayerOptions::UseBathymetry::set(bool b)
{
	asoeSimpleOceanLayerOptions()->useBathymetry() = b;
	NotifyChanged("UseBathymetry");
}

String^ gEarthPack::oepSimpleOceanLayerOptions::TextureUrl::get()
{
	return marshal_as<String^>(asoeSimpleOceanLayerOptions()->texture().value().full());
}

void gEarthPack::oepSimpleOceanLayerOptions::TextureUrl::set(String^ url)
{
	asoeSimpleOceanLayerOptions()->texture()= marshal_as<std::string>(url);
	NotifyChanged("TextureUrl");
}

unsigned gEarthPack::oepSimpleOceanLayerOptions::TextureLOD::get()
{
	return asoeSimpleOceanLayerOptions()->textureLOD().value();
}

void gEarthPack::oepSimpleOceanLayerOptions::TextureLOD::set(unsigned v)
{
	asoeSimpleOceanLayerOptions()->textureLOD() = v;
	NotifyChanged("TextureLOD");
}
