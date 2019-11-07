#include "stdafx.h"
#include "MeasureSlopeAspectHandler.h"

using namespace gEarthPack;
using namespace osgEarth;
using namespace osgEarth::Util;
using namespace osgEarth::Symbology;
using namespace osgEarth::Features;
using namespace osgEarth::Annotation;

MeasureSlopeAspectHandler::MeasureSlopeAspectHandler(osgEarth::MapNode* mapNode): MeasureBaseHandler(mapNode)
{
	setMapNode(mapNode);
}


MeasureSlopeAspectHandler::~MeasureSlopeAspectHandler()
{

}

void MeasureSlopeAspectHandler::addEventHandler(MeasureSlopeAspectEventHandler* handler)
{
	_eventHandlers.push_back(handler);
}

bool MeasureSlopeAspectHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	if (ea.getHandled())
	{
		return false;
	}

	osgViewer::View* view = static_cast<osgViewer::View*>(aa.asView());

	if (ea.getEventType() == osgGA::GUIEventAdapter::RELEASE && ea.getButton() == _mouseButton)
	{
		osg::Vec3d p, n;
		if (getLocationAt(view, ea.getX(), ea.getY(), p, n))
		{
			double slope = 0.0;
			double aspect = 0.0;
			if (calSlopeAspectDegree(p, n, slope, aspect))
			{
				osg::Vec3f eye, center, up;
				view->getCamera()->getViewMatrixAsLookAt(eye, center, up);

				osg::Vec3d pxyz = latlnghigh2xyz(p);
				float len = (eye - pxyz).length() / 10.f;

				_feature->getGeometry()->clear();
				osg::Vec3 secondp = pxyz+n*len;
				secondp = xyz2latlnghigh(secondp);
				_feature->getGeometry()->push_back(p);
				_feature->getGeometry()->push_back(secondp);
				_featureNode->init();
				_slope = slope;
				_aspect = aspect;
				_point = p;
				fireMeasureChanged();
			}
		}
		else
		{
			clear();
		}
		
		aa.requestRedraw();
	}

	return false;
}

osgEarth::Features::Feature* MeasureSlopeAspectHandler::createFeature()
{
	// Define the path feature:
	Feature* feature = new Feature(new LineString(), getMapNode()->getMapSRS());
	feature->geoInterp() = _geoInterpolation;

	// offset to mitigate Z fighting
	RenderSymbol* render = feature->style()->getOrCreate<RenderSymbol>();
	render->depthOffset()->enabled() = true;
	render->depthOffset()->automatic() = true;

	// define a style for the line
	LineSymbol* ls = feature->style()->getOrCreate<LineSymbol>();
	ls->stroke()->color() = Color::Yellow;
	ls->stroke()->width() = 2.0f;
	ls->stroke()->widthUnits() = Units::PIXELS;
	ls->tessellation() = 150;

	return feature;
}

void MeasureSlopeAspectHandler::fireMeasureChanged()
{
	for (MeasureSlopeAspectEventHandlerList::const_iterator i = _eventHandlers.begin(); i != _eventHandlers.end(); ++i)
	{
		i->get()->onSlopeAspectChanged(this, _slope,_aspect,_point);
	}
}

void MeasureSlopeAspectHandler::clear()
{
	_slope = 0.f;
	_aspect = 0.f;
	_point = osg::Vec3();
	MeasureBaseHandler::clear();
}

bool MeasureSlopeAspectHandler::calSlopeAspectDegree(const osg::Vec3d& p, const osg::Vec3d& n, double &slope, double &aspect)
{
	if (!getMapNode())
	{
		return false;
	}

	osg::Vec3d xAxis, zAxis, yAxis, northVec;

	northVec = osg::Vec3d(0.0, 0.0, 1.0);

	if (!getMapNode()->getMapSRS()->isProjected())
	{
		//fÎªzÖá
		zAxis = p;
		zAxis.normalize();
		xAxis = northVec^zAxis;
		xAxis.normalize();
		yAxis = zAxis^xAxis;
		yAxis.normalize();

	}
	else
	{
		yAxis = osg::Vec3d(0.0, 1.0, 0.0);
		zAxis = northVec;
		xAxis = yAxis^zAxis;
		xAxis.normalize();

	}

	slope = n*zAxis;
	if (slope < 0.0)
	{
		slope = 0.0;
	}
	slope = acos(slope);
	slope = osg::RadiansToDegrees(slope);
	if (slope <= 0.0001)
	{
		slope = -1.0;
		aspect = 0.0;
		return true;
	}


	osg::Vec3d targetToEye, targetToProjZ, targetToProjXY;
	float len = 100.0;

	targetToEye = n*len;
	targetToProjZ = zAxis*((targetToEye*zAxis) / (zAxis*zAxis));
	targetToProjXY = targetToEye - targetToProjZ;
	targetToProjXY.normalize();

	if (yAxis*targetToProjXY >= 1.0)
	{
		aspect = 0.0;
	}
	else if (yAxis*targetToProjXY <= -1.0)
	{
		aspect = 180.0;
	}
	else
	{
		aspect = osg::RadiansToDegrees(acos(yAxis*targetToProjXY));
		if ((targetToProjXY*xAxis) < 0)
		{
			aspect = 360.0 - aspect;
		}
	}

	return true;

}