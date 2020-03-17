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
	_driver->bind<FeatureSourceOptions>(as<FeatureModelLayerOptions>()->featureSource(),false);
	_styles = gcnew oepStyleSheet();
	_styles->bind(as<FeatureModelLayerOptions>()->styles());
	_layout = gcnew oepFeatureDisplayLayout();
	_layout->bind(as<FeatureModelLayerOptions>()->layout(),false);
	_featureName = gcnew oepStringExpression();
	_featureName->bind(as<FeatureModelLayerOptions>()->GeometryCompilerOptions::featureName(), false);
	_featureIndexing = gcnew oepFeatureSourceIndexOptions();
	_featureIndexing->bind(as<FeatureModelLayerOptions>()->featureIndexing(), false);
	_fading = gcnew oepFadeOptions();
	_fading->bind(as<FeatureModelLayerOptions>()->fading(), false);
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
	FeatureModelLayerOptions* to = as<FeatureModelLayerOptions>();
	if (to != NULL && _driver!=nullptr)
	{
		to->featureSource() = *(_driver->as<FeatureSourceOptions>());
	}
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
	FeatureModelLayerOptions* to = as<FeatureModelLayerOptions>();
	if (to != NULL && _layout != nullptr)
	{
		to->layout() = *(_driver->as<FeatureDisplayLayout>());
	}
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
	FeatureModelLayerOptions* to = as<FeatureModelLayerOptions>();
	if (to != NULL && _featureName != nullptr)
	{
		to->GeometryCompilerOptions::featureName() = *(_driver->as<StringExpression>());
	}
}

oepFeatureSourceIndexOptions^ oepFeatureModelLayerOptions::FeatureIndexing::get()
{
	return _featureIndexing;
}

void oepFeatureModelLayerOptions::FeatureIndexing::set(oepFeatureSourceIndexOptions^ p)
{
	_featureIndexing = p;
	FeatureModelLayerOptions* to = as<FeatureModelLayerOptions>();
	if (to != NULL && _featureIndexing != nullptr)
	{
		to->featureIndexing() = *(_driver->as<FeatureSourceIndexOptions>());
	}
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
	FeatureModelLayerOptions* to = as<FeatureModelLayerOptions>();
	if (to != NULL && _fading != nullptr)
	{
		to->fading() = *(_driver->as<FadeOptions>());
	}
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
	return (oepResampleMode)(as<FeatureModelLayerOptions>()->resampleMode().value());
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
	return (oepShaderPolicy)(as<FeatureModelLayerOptions>()->shaderPolicy().value());
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
