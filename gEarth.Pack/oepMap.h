#pragma once

#include "oepLayer.h"
#include "oepExtension.h"
#include "oepRefObject.h"

using namespace System;

namespace gEarthPack 
{
	public ref class oepMap : public oepRefObject
	{
	public:
		oepMap();

	public:

		virtual property String^ Name
		{
			String^ get() override;
			void set(String^ v) override;
		}

		property oepLayers^ Layers
		{
			oepLayers^ get();
		}

		property oepExtensions^ Extensions
		{
			oepExtensions^ get();
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

		osgEarth::Map* getMap();
		osgEarth::MapNode* getMapNode();

	private:

		void InitLayers();
		void InitExtensions();
		void OnLayersCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e);
		void OnExtensionsCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e);

	private:

		oepLayers^ _layers;
		oepExtensions^ _extensions;
		String^ _url;
	};
}
