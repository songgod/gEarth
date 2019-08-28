#include "stdafx.h"
#include "MeasureHeightHandler.h"

using namespace gEarthPack;

MeasureHeightHandler::MeasureHeightHandler(osgEarth::MapNode* pMapNode)
{
}


MeasureHeightHandler::~MeasureHeightHandler()
{
}

bool gEarthPack::MeasureHeightHandler::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	return false;
}

void gEarthPack::MeasureHeightHandler::setMapNode(osgEarth::MapNode* mapNode)
{

}

void gEarthPack::MeasureHeightHandler::rebuild()
{

}

void gEarthPack::MeasureHeightHandler::fireAreaChanged()
{

}

bool gEarthPack::MeasureHeightHandler::getLocationAt(osgViewer::View* view, double x, double y, double &lon, double &lat)
{
	return true;
}

void gEarthPack::MeasureHeightHandler::clear()
{
	
}
