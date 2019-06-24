#pragma once
#include "oepObject.h"
#include <osgEarth/Config>
namespace gEarthPack
{
	public ref class oepConfigOptions : oepObject
	{
	public:
		oepConfigOptions();
		~oepConfigOptions();
		!oepConfigOptions();

	public:

		osgEarth::ConfigOptions* getoeConfigOptions();

	protected:

		osgEarth::ConfigOptions* _handle;
	};
}

