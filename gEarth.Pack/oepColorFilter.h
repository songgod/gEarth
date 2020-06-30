#pragma once
#include "oepRefObject.h"

using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	public ref class oepColorFilter : public oepRefObject<osgEarth::ColorFilter>
	{
	public:
		oepColorFilter();

	public:

		virtual void Reset(){}
	};

	public ref class oepColorFilters : public ObservableCollection<oepColorFilter^>
	{
	public:
		oepColorFilters(){}
	};
}


