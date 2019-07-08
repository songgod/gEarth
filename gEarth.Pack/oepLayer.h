#pragma once

#include "oepObject.h"
#include "oepLayerOptions.h"
#include "Handle.h"
#include <osgEarth/Layer>

using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	public ref class oepLayer : public oepObject
	{
	public:
		oepLayer();
		~oepLayer();
		!oepLayer();

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

		void quit();
		osgEarth::Layer* asoeLayer();

	protected:

		typedef Handle<osgEarth::Layer> LayerHandle;
		LayerHandle* _handle;
	};

	public ref class oepLayers : public ObservableCollection<oepLayer^>
	{
	public:
		oepLayers(){}
	};
}

