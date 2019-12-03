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
	_driver->bind(&(as<FeatureModelLayerOptions>()->featureSource().mutable_value()),false);
	_styles = gcnew oepStyleSheet();
	_styles->bind(as<FeatureModelLayerOptions>()->styles());
	_layout = gcnew oepFeatureDisplayLayout();
	_layout->bind(&(as<FeatureModelLayerOptions>()->layout().mutable_value()),false);
	_featureName = gcnew oepStringExpression();
	_featureName->bind(&(as<FeatureModelLayerOptions>()->GeometryCompilerOptions::featureName().mutable_value()), false);
	_featureIndexing = gcnew oepFeatureSourceIndexOptions();
	_featureIndexing->bind(&(as<FeatureModelLayerOptions>()->featureIndexing().mutable_value()), false);
	_fading = gcnew oepFadeOptions();
	_fading->bind(&(as<FeatureModelLayerOptions>()->fading().mutable_value()), false);
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
	_driver = v;
	FeatureSourceOptions &fso = as<FeatureModelLayerOptions>()->featureSource().mutable_value();
	_driver->getVal(fso);
	_driver->bind(&fso, false);
}

oepStyleSheet^ oepFeatureModelLayerOptions::Styles::get()
{
	return _styles;
}

void oepFeatureModelLayerOptions::Styles::set(oepStyleSheet^ p)
{
	_styles = p;
	as<FeatureModelLayerOptions>()->styles() = _styles->ref();
}

double oepFeatureModelLayerOptions::MaxGranularity::get()
{
	return as<FeatureModelLayerOptions>()->GeometryCompilerOptions::maxGranularity().value();
}

void oepFeatureModelLayerOptions::MaxGranularity::set(double p)
{
	as<FeatureModelLayerOptions>()->GeometryCompilerOptions::maxGranularity() = p;
}

bool oepFeatureModelLayerOptions::EnableLighting::get()
{
	return as<FeatureModelLayerOptions>()->enableLighting().value();
}

void oepFeatureModelLayerOptions::EnableLighting::set(bool p)
{
	as<FeatureModelLayerOptions>()->enableLighting() = p;
}

oepFeatureDisplayLayout^ oepFeatureModelLayerOptions::Layout::get()
{
	return _layout;
}

void oepFeatureModelLayerOptions::Layout::set(oepFeatureDisplayLayout^ p)
{
	_layout = p;
	FeatureDisplayLayout &fso = as<FeatureModelLayerOptions>()->layout().mutable_value();
	_layout->getVal(fso);
	_layout->bind(&fso, false);
}

bool oepFeatureModelLayerOptions::ClusterCulling::get()
{
	return as<FeatureModelLayerOptions>()->clusterCulling().value();
}

void oepFeatureModelLayerOptions::ClusterCulling::set(bool p)
{
	as<FeatureModelLayerOptions>()->clusterCulling() = p;
}

oepStringExpression^ oepFeatureModelLayerOptions::FeatureName::get()
{
	return _featureName;
}

void oepFeatureModelLayerOptions::FeatureName::set(oepStringExpression^ p)
{
	_featureName = p;
	StringExpression &fso = as<FeatureModelLayerOptions>()->GeometryCompilerOptions::featureName().mutable_value();
	_featureName->getVal(fso);
	_featureName->bind(&fso, false);
}

oepFeatureSourceIndexOptions^ oepFeatureModelLayerOptions::FeatureIndexing::get()
{
	return _featureIndexing;
}

void oepFeatureModelLayerOptions::FeatureIndexing::set(oepFeatureSourceIndexOptions^ p)
{
	_featureIndexing = p;
	FeatureSourceIndexOptions &fso = as<FeatureModelLayerOptions>()->featureIndexing().mutable_value();
	_featureIndexing->getVal(fso);
	_featureIndexing->bind(&fso, false);
}

bool oepFeatureModelLayerOptions::BackfaceCulling::get()
{
	return as<FeatureModelLayerOptions>()->backfaceCulling().value();
}

void oepFeatureModelLayerOptions::BackfaceCulling::set(bool p)
{
	as<FeatureModelLayerOptions>()->backfaceCulling() = p;
}

bool oepFeatureModelLayerOptions::AlphaBlending::get()
{
	return as<FeatureModelLayerOptions>()->alphaBlending().value();
}

void oepFeatureModelLayerOptions::AlphaBlending::set(bool p)
{
	as<FeatureModelLayerOptions>()->alphaBlending() = p;
}

oepFadeOptions^ oepFeatureModelLayerOptions::Fading::get()
{
	return _fading;
}

void oepFeatureModelLayerOptions::Fading::set(oepFadeOptions^ p)
{
	_fading = p;
	FadeOptions &fso = as<FeatureModelLayerOptions>()->fading().mutable_value();
	_fading->getVal(fso);
	_fading->bind(&fso, false);
}

bool oepFeatureModelLayerOptions::NodeCaching::get()
{
	return as<FeatureModelLayerOptions>()->nodeCaching().value();
}

void oepFeatureModelLayerOptions::NodeCaching::set(bool p)
{
	as<FeatureModelLayerOptions>()->nodeCaching() = p;
}

bool oepFeatureModelLayerOptions::SessionWideResourceCache::get()
{
	return as<FeatureModelLayerOptions>()->sessionWideResourceCache().value();
}

void oepFeatureModelLayerOptions::SessionWideResourceCache::set(bool p)
{
	as<FeatureModelLayerOptions>()->sessionWideResourceCache() = p;
}

oepGeoInterpolation oepFeatureModelLayerOptions::GeoInterp::get()
{
	return (oepGeoInterpolation)as<FeatureModelLayerOptions>()->geoInterp().value();
}

void oepFeatureModelLayerOptions::GeoInterp::set(oepGeoInterpolation p)
{
	as<FeatureModelLayerOptions>()->geoInterp() = (GeoInterpolation)p;
}

bool oepFeatureModelLayerOptions::MergeGeometry::get()
{
	return as<FeatureModelLayerOptions>()->mergeGeometry().value();
}

void oepFeatureModelLayerOptions::MergeGeometry::set(bool p)
{
	as<FeatureModelLayerOptions>()->mergeGeometry() = p;
}

bool oepFeatureModelLayerOptions::Clustering::get()
{
	return as<FeatureModelLayerOptions>()->clustering().value();
}

void oepFeatureModelLayerOptions::Clustering::set(bool p)
{
	as<FeatureModelLayerOptions>()->clustering() = p;
}

bool oepFeatureModelLayerOptions::Instancing::get()
{
	return as<FeatureModelLayerOptions>()->instancing().value();
}

void oepFeatureModelLayerOptions::Instancing::set(bool p)
{
	as<FeatureModelLayerOptions>()->instancing() = p;
}

bool oepFeatureModelLayerOptions::IgnoreAltitudeSymbol::get()
{
	return as<FeatureModelLayerOptions>()->ignoreAltitudeSymbol().value();
}

void oepFeatureModelLayerOptions::IgnoreAltitudeSymbol::set(bool p)
{
	as<FeatureModelLayerOptions>()->ignoreAltitudeSymbol() = p;
}

oepResampleMode oepFeatureModelLayerOptions::ResampleMode::get()
{
	return (oepResampleMode)(as<FeatureModelLayerOptions>()->resampleMode().mutable_value());
}

void oepFeatureModelLayerOptions::ResampleMode::set(oepResampleMode p)
{
	as<FeatureModelLayerOptions>()->resampleMode() = (osgEarth::Features::ResampleFilter::ResampleMode)p;
}

double oepFeatureModelLayerOptions::ResampleMaxLength::get()
{
	return as<FeatureModelLayerOptions>()->resampleMaxLength().value();
}

void oepFeatureModelLayerOptions::ResampleMaxLength::set(double p)
{
	as<FeatureModelLayerOptions>()->resampleMaxLength() = p;
}

oepShaderPolicy oepFeatureModelLayerOptions::ShaderPolicy::get()
{
	return (oepShaderPolicy)(as<FeatureModelLayerOptions>()->shaderPolicy().mutable_value());
}

void oepFeatureModelLayerOptions::ShaderPolicy::set(oepShaderPolicy p)
{
	as<FeatureModelLayerOptions>()->shaderPolicy() = (osgEarth::ShaderPolicy)p;
}

bool oepFeatureModelLayerOptions::OptimizeStateSharing::get()
{
	return as<FeatureModelLayerOptions>()->optimizeStateSharing().value();
}

void oepFeatureModelLayerOptions::OptimizeStateSharing::set(bool p)
{
	as<FeatureModelLayerOptions>()->optimizeStateSharing() = p;
}

bool oepFeatureModelLayerOptions::Optimize::get()
{
	return as<FeatureModelLayerOptions>()->optimize().value();
}

void oepFeatureModelLayerOptions::Optimize::set(bool p)
{
	as<FeatureModelLayerOptions>()->optimize() = p;
}

bool oepFeatureModelLayerOptions::OptimizeVertexOrdering::get()
{
	return as<FeatureModelLayerOptions>()->optimizeVertexOrdering().value();
}

void oepFeatureModelLayerOptions::OptimizeVertexOrdering::set(bool p)
{
	as<FeatureModelLayerOptions>()->optimizeVertexOrdering() = p;
}

bool oepFeatureModelLayerOptions::Validate::get()
{
	return as<FeatureModelLayerOptions>()->validate().value();
}

void oepFeatureModelLayerOptions::Validate::set(bool p)
{
	as<FeatureModelLayerOptions>()->validate() = p;
}

float oepFeatureModelLayerOptions::MaxPolygonTilingAngle::get()
{
	return as<FeatureModelLayerOptions>()->maxPolygonTilingAngle().value();
}

void oepFeatureModelLayerOptions::MaxPolygonTilingAngle::set(float p)
{
	as<FeatureModelLayerOptions>()->maxPolygonTilingAngle() = p;
}

bool oepFeatureModelLayerOptions::UseGPUScreenSpaceLines::get()
{
	return as<FeatureModelLayerOptions>()->useGPUScreenSpaceLines().value();
}

void oepFeatureModelLayerOptions::UseGPUScreenSpaceLines::set(bool p)
{
	as<FeatureModelLayerOptions>()->useGPUScreenSpaceLines() = p;
}
