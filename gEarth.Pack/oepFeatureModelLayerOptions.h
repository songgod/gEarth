#pragma once
#include "oepVisibleLayerOptions.h"
#include "oepFeatureSourceOptions.h"
#include "oepFeatureDisplayLayout.h"
#include "oepStringExpression.h"
#include "oepFeatureSourceIndexOptions.h"
#include "oepFadeOptions.h"
#include "oepGeoCommon.h"
#include "oepStyleSheet.h"

namespace gEarthPack
{
	public ref class oepFeatureModelLayerOptions :
		public oepVisibleLayerOptions
	{
	public:
		oepFeatureModelLayerOptions();

	public:

		property oepFeatureSourceOptions^ driver
		{
			oepFeatureSourceOptions^ get();
			void set(oepFeatureSourceOptions^ v);
		}

		property oepStyleSheet^ Styles
		{
			oepStyleSheet^ get();
			void set(oepStyleSheet^ p);
		}

		property double MaxGranularity
		{
			double get();
			void set(double p);
		}

		property bool EnableLighting
		{
			bool get();
			void set(bool p);
		}

		property oepFeatureDisplayLayout^ Layout
		{
			oepFeatureDisplayLayout^ get();
			void set(oepFeatureDisplayLayout^ p);
		}
		
		property bool ClusterCulling
		{
			bool get();
			void set(bool p);
		}
		
		property oepStringExpression^ FeatureName
		{
			oepStringExpression^ get();
			void set(oepStringExpression^ p);
		}

		property oepFeatureSourceIndexOptions^ FeatureIndexing
		{
			oepFeatureSourceIndexOptions^ get();
			void set(oepFeatureSourceIndexOptions^ p);
		}

		property bool BackfaceCulling
		{
			bool get();
			void set(bool p);
		}

		property bool AlphaBlending
		{
			bool get();
			void set(bool p);
		}

		property oepFadeOptions^ Fading
		{
			oepFadeOptions^ get();
			void set(oepFadeOptions^ p);
		}

		property bool NodeCaching
		{
			bool get();
			void set(bool p);
		}

		property bool SessionWideResourceCache
		{
			bool get();
			void set(bool p);
		}

		property oepGeoInterpolation GeoInterp
		{
			oepGeoInterpolation get();
			void set(oepGeoInterpolation p);
		}

		property bool MergeGeometry
		{
			bool get();
			void set(bool p);
		}

		property bool Clustering
		{
			bool get();
			void set(bool p);
		}

		property bool Instancing
		{
			bool get();
			void set(bool p);
		}

		property bool IgnoreAltitudeSymbol
		{
			bool get();
			void set(bool p);
		}

		property oepResampleMode ResampleMode
		{
			oepResampleMode get();
			void set(oepResampleMode p);
		}

		property double ResampleMaxLength
		{
			double get();
			void set(double p);
		}

		property oepShaderPolicy ShaderPolicy
		{
			oepShaderPolicy get();
			void set(oepShaderPolicy p);
		}

		property bool OptimizeStateSharing
		{
			bool get();
			void set(bool p);
		}

		property bool Optimize
		{
			bool get();
			void set(bool p);
		}

		property bool OptimizeVertexOrdering
		{
			bool get();
			void set(bool p);
		}

		property bool Validate
		{
			bool get();
			void set(bool p);
		}

		property float MaxPolygonTilingAngle
		{
			float get();
			void set(float p);
		}

		property bool UseGPUScreenSpaceLines
		{
			bool get();
			void set(bool p);
		}

	internal:

		virtual void binded() override;
		virtual void unbinded() override;

	private:

		oepFeatureSourceOptions^ _driver;
		oepStyleSheet^ _styles;
		oepFeatureDisplayLayout^ _layout;
		oepStringExpression^ _featureName;
		oepFeatureSourceIndexOptions^ _featureIndexing;
		oepFadeOptions^ _fading;
	};
}

