#pragma once
#include "oepRefObject.h"

using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	public ref class oepColorFilter : public oepRefObject
	{
	public:
		oepColorFilter();

	public:

		virtual void Reset(){}

	internal:

		osgEarth::ColorFilter* ntColorFilter() { return as<osgEarth::ColorFilter>(); }
	};

	public ref class oepColorFilters : public ObservableCollection<oepColorFilter^>
	{
	public:
		oepColorFilters(){}
	};
}


