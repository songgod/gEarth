#pragma once
#include "oepValObject.h"
#include "oepValVector.h"

using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	public ref class oepConfigOptions : public oepValObject<osgEarth::ConfigOptions>
	{
	public:
		oepConfigOptions();
	};

	public ref class oepConfigOptionsCollection : oepValVector<oepConfigOptions,osgEarth::ConfigOptions>
	{

	};
}

