// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#include <windows.h> 
#include <msclr\marshal_cppstd.h> 

//osgEarth
#include <osgEarth/Map>
#include <osgEarth/MapNode>
#include <osgEarth/Layer>
#include <osgEarth/ColorFilter>
#include <osgEarth/Viewpoint>
#include <osgEarth/Extension>
#include <osgEarth/GeoCommon>
#include <osgEarth/GLUtils>
#include <osgEarth/GeoMath>
#include <osgEarth/TerrainEngineNode>
#include <osgEarth/Config>
#include <osgEarth/ElevationLayer>
#include <osgEarth/ImageLayer>
#include <osgEarth/TerrainLayer>
#include <osgEarth/Layer>
#include <osgEarth/VisibleLayer>
#include <osgEarth/TileSource>
#include <osgEarth/ModelLayer>

#include <osgEarthUtil/BrightnessContrastColorFilter>
#include <osgEarthUtil/ChromaKeyColorFilter>
#include <osgEarthUtil/CMYKColorFilter>
#include <osgEarthUtil/GammaColorFilter>
#include <osgEarthUtil/HSLColorFilter>
#include <osgEarthUtil/RGBColorFilter>
#include <osgEarthUtil/MeasureTool>
#include <osgEarthUtil/ViewFitter>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthUtil/SimpleOceanLayer>
#include <osgEarthUtil/ViewFitter>
#include <osgEarthUtil/TerrainProfile>
#include <osgEarthUtil/LinearLineOfSight>
#include <osgEarthUtil/RadialLineOfSight>
#include <osgEarthUtil/ContourMap>

#include <osgEarthDrivers/sky_simple/SimpleSkyOptions>
#include <osgEarthDrivers/viewpoints/ViewpointsOptions>
#include <osgEarthDrivers/arcgis/ArcGISOptions>
#include <osgEarthDrivers/bing/BingOptions>
#include <osgEarthDrivers/gdal/GDALOptions>
#include <osgEarthDrivers/feature_elevation/FeatureElevationOptions>
#include <osgEarthDrivers/feature_ogr/OGRFeatureOptions>

#include <osgEarthAnnotation/FeatureNode>

#include <osgEarthSymbology/Style>
#include <osgEarthSymbology/StyleSheet>
#include <osgEarthSymbology/Symbol>
#include <osgEarthSymbology/Geometry>

#include <osgEarthFeatures/GeometryUtils>
#include <osgEarthFeatures/FeatureModelLayer>
#include <osgEarthFeatures/FeatureModelSource>

//osg
#include <osg/ref_ptr>
#include <osg/Vec3d>
#include <osg/Vec2f>
#include <osg/Vec3f>
#include <osg/Vec4f>
#include <osg/AnimationPath>
#include <osg/Group>
#include <osg\ComputeBoundsVisitor>
#include <osg/TriangleFunctor>

#include <osgGA/GUIEventHandler>
#include <osgGA/AnimationPathManipulator>
#include <osgGA\StateSetManipulator>
#include <osgGA/TrackballManipulator>

#include <osgViewer/View>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer\api\win32\GraphicsWindowWin32>
#include <osgDB/FileUtils>
#include <osgDB/FileNameUtils>
#include <osgDB\ReadFile>
#include <osgDB\WriteFile>
#include <osgDB/ReaderWriter>
#include <osgDB/Registry>

#include <osgUtil/Tessellator>

#include <OpenThreads\ScopedLock>
#include <OpenThreads/Thread>
#include <OpenThreads/Block>