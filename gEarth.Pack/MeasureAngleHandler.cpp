#include "stdafx.h"
#include "MeasureAngleHandler.h"

#define LC "[MeasureTool] "

using namespace gEarthPack;
using namespace osgEarth;
using namespace osgEarth::Util;
using namespace osgEarth::Symbology;
using namespace osgEarth::Features;
using namespace osgEarth::Annotation;

MeasureAngleHandler::MeasureAngleHandler():_bNewMesura(true)
{

}


MeasureAngleHandler::~MeasureAngleHandler()
{

}

void MeasureAngleHandler::addEventHandler(MeasureAngleEventHandler* handler)
{
	_eventHandlers.push_back(handler);
}

bool MeasureAngleHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	if (ea.getHandled())
	{
		return false;
	}


	osgViewer::View* view = static_cast<osgViewer::View*>(aa.asView());
	if(ea.getEventType() == osgGA::GUIEventAdapter::RELEASE && ea.getButton() == _mouseButton)
	{
		if(_bNewMesura)
			clear();

		osg::Vec3d p, n;
		if (getLocationAt(view, ea.getX(), ea.getY(), p, n))
		{
			if (_feature->getGeometry()->size() > 0)
				_feature->getGeometry()->back() = p;
			else
				_feature->getGeometry()->push_back(p);

			_bNewMesura = _feature->getGeometry()->size() == 3;

			if(_feature->getGeometry()->size()<3)
				_feature->getGeometry()->push_back(p);
			_featureNode->init();
		}

		fireMeasureChanged();
		aa.requestRedraw();
	}
	else if (ea.getEventType() == osgGA::GUIEventAdapter::MOVE)
	{
		if (!_bNewMesura)
		{
			osg::Vec3d p, n;
			if (getLocationAt(view, ea.getX(), ea.getY(), p, n))
			{
				_feature->getGeometry()->back() = p;
				_featureNode->init();
				fireMeasureChanged();
				aa.requestRedraw();
			}
		}
	}
	return false;
}

osgEarth::Features::Feature * MeasureAngleHandler::createFeature()
{
	// Define the path feature:
	Feature* feature = new Feature(new LineString(), getMapNode()->getMapSRS());
	feature->geoInterp() = _geoInterpolation;

	// clamp to the terrain skin as it pages in
	AltitudeSymbol* alt = feature->style()->getOrCreate<AltitudeSymbol>();
	alt->clamping() = alt->CLAMP_TO_TERRAIN;
	alt->technique() = alt->TECHNIQUE_GPU;

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

void MeasureAngleHandler::clear()
{
	_bNewMesura = true;
	MeasureBaseHandler::clear();
}

void MeasureAngleHandler::fireMeasureChanged()
{
	std::vector<osg::Vec3d> poss = _feature->getGeometry()->asVector();
	if (poss.size() != 3)
		return;

	poss[0].z() = 0.0;
	poss[1].z() = 0.0;
	poss[2].z() = 0.0;

	double a = (poss[2] - poss[0]).length2();
	double b = (poss[1] - poss[0]).length2();
	double c = (poss[2] - poss[1]).length2();

	double cosangle = (b + c - a) / (sqrt(b)*sqrt(c) * 2);
	double angle = acos(cosangle);
	angle = osg::RadiansToDegrees(angle);

	for (MeasureAngleEventHandlerList::const_iterator i = _eventHandlers.begin(); i != _eventHandlers.end(); ++i)
	{
		i->get()->onAngleChanged(this, angle);
	}
}
