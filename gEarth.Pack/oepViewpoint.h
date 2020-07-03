#pragma once

#include "oepValObject.h"

using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	public ref class oepViewpoint : public oepValObject
	{
	public:
		oepViewpoint();

	public:

		virtual property String^ Name
		{
			String^ get() override;
			void set(String^ v) override;
		}

		property bool IsValid
		{
			bool get();
		}

	internal:

		oepViewpoint(osgEarth::Viewpoint& vp);

	internal:

		virtual void delelehandle() override;
	};

	public ref class oepViewPoints : public ObservableCollection<oepViewpoint^>
	{

	};
}

