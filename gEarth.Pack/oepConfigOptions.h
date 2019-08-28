#pragma once
#include "oepObject.h"

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

