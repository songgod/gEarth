#pragma once

#include "oepRefObject.h"
#include "oepLayerOptions.h"

using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	public ref class oepLayer : public oepRefObject
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

	internal:

		osgEarth::Layer* ntLayer() { return as<osgEarth::Layer>(); }
	};

	public ref class oepLayers : public ObservableCollection<oepLayer^>
	{
	public:
		oepLayers(){}
	};
}

