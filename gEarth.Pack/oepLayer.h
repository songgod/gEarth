#pragma once

#include "oepRefObject.h"
#include "oepLayerOptions.h"
#include "oepHandle.h"

using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	public ref class oepLayer : public oepRefObject<osgEarth::Layer>
	{
	public:
		oepLayer();

	public:

		virtual property String^ Name
		{
			String^ get() override;
			void set(String^ v) override;
		}

		property bool IsOK
		{
			bool get();
		}

		property String^ StatusString
		{
			String^ get();
		}
	};

	public ref class oepLayers : public ObservableCollection<oepLayer^>
	{
	public:
		oepLayers(){}
	};
}

