#pragma once
#include "oepValObject.h"
#include "oepValVector.h"

using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	public ref class oepConfigOptions : public oepValObject
	{
	public:
		oepConfigOptions();

	internal:

		virtual void delelehandle() override;
	};

	public ref class oepConfigOptionsCollection : oepValVector<oepConfigOptions,osgEarth::ConfigOptions>
	{

	};
}

