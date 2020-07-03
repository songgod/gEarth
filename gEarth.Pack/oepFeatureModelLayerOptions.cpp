#include "stdafx.h"
#include "oepFeatureModelLayerOptions.h"
#include <osgEarthFeatures/FeatureModelLayer>

using namespace gEarthPack;
using namespace osgEarth::Features;

oepFeatureModelLayerOptions::oepFeatureModelLayerOptions()
{
	bind(new FeatureModelLayerOptions(),true);
}

void oepFeatureModelLayerOptions::binded()
{
	_driver = gcnew oepFeatureSourceOptions();
	_driver->bind(as<FeatureModelLayerOptions>()->featureSource());
	_styles = gcnew oepStyleSheet();
	_styles->bind(as<FeatureModelLayerOptions>()->styles());
	_layout = gcnew oepFeatureDisplayLayout();
	_layout->bind(as<FeatureModelLayerOptions>()->layout());
	_featureName = gcnew oepStringExpression();
	_featureName->bind(as<FeatureModelLayerOptions>()->GeometryCompilerOptions::featureName());
	_featureIndexing = gcnew oepFeatureSourceIndexOptions();
	_featureIndexing->bind(as<FeatureModelLayerOptions>()->featureIndexing());
	_fading = gcnew oepFadeOptions();
	_fading->bind(as<FeatureModelLayerOptions>()->fading());
}

void oepFeatureModelLayerOptions::unbinded()
{
	_driver->unbind();
}

oepFeatureSourceOptions^ oepFeatureModelLayerOptions::driver::get()
{
	return _driver;
}

void oepFeatureModelLayerOptions::driver::set(oepFeatureSourceOptions^ v)
{
	FeatureModelLayerOptions* to = as<FeatureModelLayerOptions>();
	if (to != NULL && v!=nullptr)
	{
		to->featureSource() = *(v->as<FeatureSourceOptions>());
		NotifyChanged("driver");
	}
}

oepStyleSheet^ oepFeatureModelLayerOptions::Styles::get()
{
	return _styles;
}

void oepFeatureModelLayerOptions::Styles::set(oepStyleSheet^ p)
{
	_styles = p;
	as<FeatureModelLayerOptions>()->styles() = _styles->as<osgEarth::Symbology::StyleSheet>();
	NotifyChanged("Styles");
}

double oepFeatureModelLayerOptions::MaxGranularity::get()
{
	return as<FeatureModelLayerOptions>()->GeometryCompilerOptions::maxGranularity().value();
}

void oepFeatureModelLayerOptions::MaxGranularity::set(double p)
{
	as<FeatureModelLayerOptions>()->GeometryCompilerOptions::maxGranularity() = p;
	NotifyChanged("MaxGranularity");
}

bool oepFeatureModelLayerOptions::EnableLighting::get()
{
	return as<FeatureModelLayerOptions>()->enableLighting().value();
}

void oepFeatureModelLayerOptions::EnableLighting::set(bool p)
{
	as<FeatureModelLayerOptions>()->enableLighting() = p;
	NotifyChanged("EnableLighting");
}

oepFeatureDisplayLayout^ oepFeatureModelLayerOptions::Layout::get()
{
	return _layout;
}

void oepFeatureModelLayerOptions::Layout::set(oepFeatureDisplayLayout^ p)
{
	FeatureModelLayerOptions* to = as<FeatureModelLayerOptions>();
	if (to != NULL && p != nullptr)
	{
		to->layout() = *(p->as<FeatureDisplayLayout>());
		NotifyChanged("Layout");
	}
}

bool oepFeatureModelLayerOptions::ClusterCulling::get()
{
	return as<FeatureModelLayerOptions>()->clusterCulling().value();
}

void oepFeatureModelLayerOptions::ClusterCulling::set(bool p)
{
	as<FeatureModelLayerOptions>()->clusterCulling() = p;
	NotifyChanged("ClusterCulling");
}

oepStringExpression^ oepFeatureModelLayerOptions::FeatureName::get()
{
	return _featureName;
}

void oepFeatureModelLayerOptions::FeatureName::set(oepStringExpression^ p)
{
	FeatureModelLayerOptions* to = as<FeatureModelLayerOptions>();
	if (to != NULL && p != nullptr)
	{
		to->GeometryCompilerOptions::featureName() = *(p->as<StringExpression>());
		NotifyChanged("FeatureName");
	}
}

oepFeatureSourceIndexOptions^ oepFeatureModelLayerOptions::FeatureIndexing::get()
{
	return _featureIndexing;
}

void oepFeatureModelLayerOptions::FeatureIndexing::set(oepFeatureSourceIndexOptions^ p)
{
	FeatureModelLayerOptions* to = as<FeatureModelLayerOptions>();
	if (to != NULL && p != nullptr)
	{
		to->featureIndexing() = *(p->as<FeatureSourceIndexOptions>());
		NotifyChanged("FeatureIndexing");
	}
}

bool oepFeatureModelLayerOptions::BackfaceCulling::get()
{
	return as<FeatureModelLayerOptions>()->backfaceCulling().value();
}

void oepFeatureModelLayerOptions::BackfaceCulling::set(bool p)
{
	as<FeatureModelLayerOptions>()->backfaceCulling() = p;
	NotifyChanged("BackfaceCulling");
}

bool oepFeatureModelLayerOptions::AlphaBlending::get()
{
	return as<FeatureModelLayerOptions>()->alphaBlending().value();
}

void oepFeatureModelLayerOptions::AlphaBlending::set(bool p)
{
	as<FeatureModelLayerOptions>()->alphaBlending() = p;
	NotifyChanged("AlphaBlending");
}

oepFadeOptions^ oepFeatureModelLayerOptions::Fading::get()
{
	return _fading;
}

void oepFeatureModelLayerOptions::Fading::set(oepFadeOptions^ p)
{
	FeatureModelLayerOptions* to = as<FeatureModelLayerOptions>();
	if (to != NULL && p != nullptr)
	{
		to->fading() = *(p->as<FadeOptions>());
		NotifyChanged("Fading");
	}
}

bool oepFeatureModelLayerOptions::NodeCaching::get()
{
	return as<FeatureModelLayerOptions>()->nodeCaching().value();
}

void oepFeatureModelLayerOptions::NodeCaching::set(bool p)
{
	as<FeatureModelLayerOptions>()->nodeCaching() = p;
	NotifyChanged("NodeCaching");
}

bool oepFeatureModelLayerOptions::SessionWideResourceCache::get()
{
	return as<FeatureModelLayerOptions>()->sessionWideResourceCache().value();
}

void oepFeatureModelLayerOptions::SessionWideResourceCache::set(bool p)
{
	as<FeatureModelLayerOptions>()->sessionWideResourceCache() = p;
	NotifyChanged("SessionWideResourceCache");
}

oepGeoInterpolation oepFeatureModelLayerOptions::GeoInterp::get()
{
	return (oepGeoInterpolation)as<FeatureModelLayerOptions>()->geoInterp().value();
}

void oepFeatureModelLayerOptions::GeoInterp::set(oepGeoInterpolation p)
{
	as<FeatureModelLayerOptions>()->geoInterp() = (GeoInterpolation)p;
	NotifyChanged("GeoInterp");
}

bool oepFeatureModelLayerOptions::MergeGeometry::get()
{
	return as<FeatureModelLayerOptions>()->mergeGeometry().value();
}

void oepFeatureModelLayerOptions::MergeGeometry::set(bool p)
{
	as<FeatureModelLayerOptions>()->mergeGeometry() = p;
	NotifyChanged("MergeGeometry");
}

bool oepFeatureModelLayerOptions::Clustering::get()
{
	return as<FeatureModelLayerOptions>()->clustering().value();
}

void oepFeatureModelLayerOptions::Clustering::set(bool p)
{
	as<FeatureModelLayerOptions>()->clustering() = p;
	NotifyChanged("Clustering");
}

bool oepFeatureModelLayerOptions::Instancing::get()
{
	return as<FeatureModelLayerOptions>()->instancing().value();
}

void oepFeatureModelLayerOptions::Instancing::set(bool p)
{
	as<FeatureModelLayerOptions>()->instancing() = p;
	NotifyChanged("Instancing");
}

bool oepFeatureModelLayerOptions::IgnoreAltitudeSymbol::get()
{
	return as<FeatureModelLayerOptions>()->ignoreAltitudeSymbol().value();
}

void oepFeatureModelLayerOptions::IgnoreAltitudeSymbol::set(bool p)
{
	as<FeatureModelLayerOptions>()->ignoreAltitudeSymbol() = p;
	NotifyChanged("IgnoreAltitudeSymbol");
}

oepResampleMode oepFeatureModelLayerOptions::ResampleMode::get()
{
	return (oepResampleMode)(as<FeatureModelLayerOptions>()->resampleMode().value());
}

void oepFeatureModelLayerOptions::ResampleMode::set(oepResampleMode p)
{
	as<FeatureModelLayerOptions>()->resampleMode() = (osgEarth::Features::ResampleFilter::ResampleMode)p;
	NotifyChanged("ResampleMode");
}

double oepFeatureModelLayerOptions::ResampleMaxLength::get()
{
	return as<FeatureModelLayerOptions>()->resampleMaxLength().value();
}

void oepFeatureModelLayerOptions::ResampleMaxLength::set(double p)
{
	as<FeatureModelLayerOptions>()->resampleMaxLength() = p;
	NotifyChanged("ResampleMaxLength");
}

oepShaderPolicy oepFeatureModelLayerOptions::ShaderPolicy::get()
{
	return (oepShaderPolicy)(as<FeatureModelLayerOptions>()->shaderPolicy().value());
}

void oepFeatureModelLayerOptions::ShaderPolicy::set(oepShaderPolicy p)
{
	as<FeatureModelLayerOptions>()->shaderPolicy() = (osgEarth::ShaderPolicy)p;
	NotifyChanged("ShaderPolicy");
}

bool oepFeatureModelLayerOptions::OptimizeStateSharing::get()
{
	return as<FeatureModelLayerOptions>()->optimizeStateSharing().value();
}

void oepFeatureModelLayerOptions::OptimizeStateSharing::set(bool p)
{
	as<FeatureModelLayerOptions>()->optimizeStateSharing() = p;
	NotifyChanged("OptimizeStateSharing");
}

bool oepFeatureModelLayerOptions::Optimize::get()
{
	return as<FeatureModelLayerOptions>()->optimize().value();
}

void oepFeatureModelLayerOptions::Optimize::set(bool p)
{
	as<FeatureModelLayerOptions>()->optimize() = p;
	NotifyChanged("Optimize");
}

bool oepFeatureModelLayerOptions::OptimizeVertexOrdering::get()
{
	return as<FeatureModelLayerOptions>()->optimizeVertexOrdering().value();
}

void oepFeatureModelLayerOptions::OptimizeVertexOrdering::set(bool p)
{
	as<FeatureModelLayerOptions>()->optimizeVertexOrdering() = p;
	NotifyChanged("OptimizeVertexOrdering");
}

bool oepFeatureModelLayerOptions::Validate::get()
{
	return as<FeatureModelLayerOptions>()->validate().value();
}

void oepFeatureModelLayerOptions::Validate::set(bool p)
{
	as<FeatureModelLayerOptions>()->validate() = p;
	NotifyChanged("Validate");
}

float oepFeatureModelLayerOptions::MaxPolygonTilingAngle::get()
{
	return as<FeatureModelLayerOptions>()->maxPolygonTilingAngle().value();
}

void oepFeatureModelLayerOptions::MaxPolygonTilingAngle::set(float p)
{
	as<FeatureModelLayerOptions>()->maxPolygonTilingAngle() = p;
	NotifyChanged("MaxPolygonTilingAngle");
}

bool oepFeatureModelLayerOptions::UseGPUScreenSpaceLines::get()
{
	return as<FeatureModelLayerOptions>()->useGPUScreenSpaceLines().value();
}

void oepFeatureModelLayerOptions::UseGPUScreenSpaceLines::set(bool p)
{
	as<FeatureModelLayerOptions>()->useGPUScreenSpaceLines() = p;
	NotifyChanged("UseGPUScreenSpaceLines");
}
