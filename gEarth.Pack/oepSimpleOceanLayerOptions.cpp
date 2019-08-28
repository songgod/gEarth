#include "stdafx.h"
#include "oepSimpleOceanLayerOptions.h"

using namespace msclr::interop;
using namespace gEarthPack;
oepSimpleOceanLayerOptions::oepSimpleOceanLayerOptions()
{
	_handle = new osgEarth::Util::SimpleOceanLayerOptions();
}

osgEarth::Util::SimpleOceanLayerOptions* oepSimpleOceanLayerOptions::asoeSimpleOceanLayerOptions()
{
	return dynamic_cast<osgEarth::Util::SimpleOceanLayerOptions*>(_handle);
}

oepVec4f oepSimpleOceanLayerOptions::Color::get()
{
	osgEarth::Color c = asoeSimpleOceanLayerOptions()->color().value();
	return oepVec4f(c.r(), c.g(), c.b(), c.a());
}

void oepSimpleOceanLayerOptions::Color::set(oepVec4f v)
{
	osgEarth::Color c(v.x, v.y, v.z, v.a);
	asoeSimpleOceanLayerOptions()->color() = c;
	NotifyChanged("Color");
}

float oepSimpleOceanLayerOptions::MaxAltitude::get()
{
	return asoeSimpleOceanLayerOptions()->maxAltitude().value();
}

void oepSimpleOceanLayerOptions::MaxAltitude::set(float v)
{
	asoeSimpleOceanLayerOptions()->maxAltitude() = v;
	NotifyChanged("MaxAltitude");
}

String^ oepSimpleOceanLayerOptions::MaskLayer::get()
{
	return marshal_as<String^>(asoeSimpleOceanLayerOptions()->maskLayer().value());
}

void oepSimpleOceanLayerOptions::MaskLayer::set(String^ v)
{
	asoeSimpleOceanLayerOptions()->maskLayer() = marshal_as<std::string>(v);
	NotifyChanged("MaskLayer");
}

bool oepSimpleOceanLayerOptions::UseBathymetry::get()
{
	return asoeSimpleOceanLayerOptions()->useBathymetry().value();
}

void oepSimpleOceanLayerOptions::UseBathymetry::set(bool b)
{
	asoeSimpleOceanLayerOptions()->useBathymetry() = b;
	NotifyChanged("UseBathymetry");
}

String^ oepSimpleOceanLayerOptions::TextureUrl::get()
{
	return marshal_as<String^>(asoeSimpleOceanLayerOptions()->texture().value().full());
}

void oepSimpleOceanLayerOptions::TextureUrl::set(String^ url)
{
	asoeSimpleOceanLayerOptions()->texture()= marshal_as<std::string>(url);
	NotifyChanged("TextureUrl");
}

unsigned oepSimpleOceanLayerOptions::TextureLOD::get()
{
	return asoeSimpleOceanLayerOptions()->textureLOD().value();
}

void oepSimpleOceanLayerOptions::TextureLOD::set(unsigned v)
{
	asoeSimpleOceanLayerOptions()->textureLOD() = v;
	NotifyChanged("TextureLOD");
}
