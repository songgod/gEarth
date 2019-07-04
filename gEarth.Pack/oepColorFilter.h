#pragma once
#include "oepObject.h"
#include "Handle.h"
#include <osgEarth/ColorFilter>

using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	public ref class oepColorFilter : public oepObject
	{
	public:
		oepColorFilter();
		~oepColorFilter();
		!oepColorFilter();

	public:

		virtual void Reset(){}

	internal:

		osgEarth::ColorFilter* asoeColorFilter();

	public:

		typedef Handle<osgEarth::ColorFilter> ColorFilterHandle;
		ColorFilterHandle* _handle;
	};

	public ref class oepColorFilters : public ObservableCollection<oepColorFilter^>
	{
	public:
		oepColorFilters(){}
	};
}


