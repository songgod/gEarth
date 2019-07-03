#include "stdafx.h"
#include "oepExtension.h"
#include <msclr\marshal_cppstd.h>  

using namespace msclr::interop;

osgEarth::Extension* createSpecialExtension(const osgEarth::Config& conf)
{
	// special support for the default sky extension:
	if (conf.key() == "sky" && !conf.hasValue("driver"))
		return osgEarth::Extension::create("sky_simple", conf);

	if (conf.key() == "ocean" && !conf.hasValue("driver"))
		return osgEarth::Extension::create("ocean_simple", conf);

	return 0L;
}

gEarthPack::oepExtension::oepExtension(oepConfigOptions^ config):_handle(NULL)
{
	if (config != nullptr && config->getoeConfigOptions() != NULL)
	{
		osgEarth::Config conf = config->getoeConfigOptions()->getConfig();
		std::string name = conf.key();
		osgEarth::Extension* extension = osgEarth::Extension::create(conf.key(), conf);
		if (!extension)
		{
			name = conf.key() + "_" + conf.value("driver");
			extension = osgEarth::Extension::create(name, conf);

			if (!extension)
				extension = createSpecialExtension(conf);
		}
		_handle = new ExtensionHandle(extension);
	}
}

osgEarth::Extension* gEarthPack::oepExtension::asoeExtension()
{
	return _handle!=NULL ? _handle->getValue() : NULL;
}

String^ gEarthPack::oepExtension::Name::get()
{
	osgEarth::Extension* pext = asoeExtension();
	if (!pext)
		return "";
	return marshal_as<String^>(pext->getName());
}

void gEarthPack::oepExtension::Name::set(String^ v)
{
	osgEarth::Extension* pext = asoeExtension();
	if (!pext)
		return;
	pext->setName(marshal_as<std::string>(v));
	NotifyChanged("Name");
}
