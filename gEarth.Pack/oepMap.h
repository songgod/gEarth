#pragma once

#include <osgEarth/MapNode>
#include "oepLayer.h"
#include "Handle.h"

using namespace System;

namespace gEarthPack 
{
	public ref class oepMap : public oepObject
	{
	public:
		oepMap();
		~oepMap();
		!oepMap();

	public:

		property oepLayers^ Layers
		{
			oepLayers^ get();
		}

		property String^ Url
		{
			String^ get();
		private:
			void set(String^ url);
		}

	public:

		bool load(String^ url);
		bool save();
		bool saveAs(String^ url);


	internal:

		void quit();
		osgEarth::Map* getMap();

	private:

		void OnCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e);

	private:

		typedef Handle<osgEarth::MapNode> MapHandle;
		MapHandle* _handle;
		oepLayers^ _layers;
		String^ _url;
	};
}
