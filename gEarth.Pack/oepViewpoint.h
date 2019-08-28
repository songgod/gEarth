#pragma once

#include "oepValObject.h"

using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	public ref class oepViewpoint : public oepValObject<osgEarth::Viewpoint>
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
		oepViewpoint(const osgEarth::Viewpoint& vp);
		void setHandle(osgEarth::Viewpoint* handle);
		void resetHandle();

	private:

		osgEarth::Viewpoint* _handle;
		bool _ownhandle;
	};

	public ref class oepViewPoints : public ObservableCollection<oepViewpoint^>
	{

	};
}

