#pragma once
#include "oepObject.h"
#include <osgEarth/Config>
namespace gEarthPack
{
	public ref class oepSource : oepObject
	{
	public:
		oepSource();
		~oepSource();
		!oepSource();

	public:

		osgEarth::ConfigOptions* getoeConfigOptions();

	protected:

		osgEarth::ConfigOptions* _handle;
	};
}

