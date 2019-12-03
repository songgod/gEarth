#include "stdafx.h"
#include "oepContourMapExtension.h"
#include "oepExtensionFactory.h"

using namespace gEarthPack;

oepContourMapExtension::oepContourMapExtension(): _bVisible(true)
{
	osgEarth::Util::ContourMapOptions options;
	osgEarth::Config conf = options.getConfig();
	conf.key() = "contour_map";
	osgEarth::Extension* extension = oepExtensionFactory::createoeExtension(conf);
	if (!extension) throw gcnew Exception("Invalid contour map extension");
	bind(extension);
}

oepContourMapExtension::oepContourMapExtension(osgEarth::Extension* ext)
{
	bind(ext);
}

osgEarth::Util::ContourMap* gEarthPack::oepContourMapExtension::getoeContourMap()
{
	if (!_handle || !_handle->getValue())
		return NULL;
	osgEarth::Util::ContourMapExtension* extension = dynamic_cast<osgEarth::Util::ContourMapExtension*>(_handle->getValue());
	if (extension == NULL)
		return NULL;
	return extension->getContourMap();
}

void gEarthPack::oepContourMapExtension::ColorMap::set(Dictionary<float, oepVec4f>^ cm)
{
	if (cm == nullptr)
		return;

	osgEarth::Util::ContourMap* pContourMap = getoeContourMap();
	if (pContourMap == NULL)
		return;

	std::map<float, osg::Vec4f> map;
	for each (KeyValuePair<float,oepVec4f>^ var in cm)
	{
		oepVec4f v = var->Value;
		map[var->Key] = osg::Vec4f(v.x, v.y, v.z, v.a);
	}

	osg::TransferFunction1D* t1d = new osg::TransferFunction1D();
	t1d->setColorMap(map);

	pContourMap->setTransferFunction(t1d);

	NotifyChanged("ColorMap");
}

Dictionary<float, gEarthPack::oepVec4f>^ gEarthPack::oepContourMapExtension::ColorMap::get()
{
	Dictionary<float, gEarthPack::oepVec4f>^ res = gcnew Dictionary<float, gEarthPack::oepVec4f>();
	osgEarth::Util::ContourMap* pContourMap = getoeContourMap();
	if (pContourMap == NULL)
		return res;

	osg::TransferFunction1D* t1d = pContourMap->getTransferFunction();
	if (t1d == NULL)
		return res;

	const osg::TransferFunction1D::ColorMap& cm = t1d->getColorMap();

	for (osg::TransferFunction1D::ColorMap::const_iterator citer = cm.begin();
		citer != cm.end(); ++citer)
	{
		res[citer->first] = oepVec4f(citer->second.r(), citer->second.g(), citer->second.b(), citer->second.a());
	}

	return res;
}