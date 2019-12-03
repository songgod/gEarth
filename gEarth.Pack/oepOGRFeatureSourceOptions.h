#pragma once
#include "oepFeatureSourceOptions.h"
#include "oepConfig.h"
#include "oepQuery.h"

namespace gEarthPack
{
	public ref class oepOGRFeatureSourceOptions :
		public oepFeatureSourceOptions
	{
	public:
		oepOGRFeatureSourceOptions();

	public:

		property String^ Url
		{
			String^ get();
			void set(String^ p);
		}

		property String^ Connection
		{
			String^ get();
			void set(String^ p);
		}

		property String^ OgrDriver
		{
			String^ get();
			void set(String^ p);
		}

		property bool BuildSpatialIndex
		{
			bool get();
			void set(bool p);
		}
		
		property bool ForceRebuildSpatialIndex
		{
			bool get();
			void set(bool p);
		}

		property oepConfig^ GeometryConfig
		{
			oepConfig^ get();
			void set(oepConfig^ p);
		}

		property String^ GeometryUrl
		{
			String^ get();
			void set(String^ p);
		}

		property String^ Layer
		{
			String^ get();
			void set(String^ p);
		}

		property oepQuery^ Query
		{
			oepQuery^ get();
			void set(oepQuery^ p);
		}

	internal:

		virtual void binded() override;
		virtual void unbinded() override;

	protected:

		oepConfig^ _geometryConfig;
		oepQuery^ _query;
	};
}

