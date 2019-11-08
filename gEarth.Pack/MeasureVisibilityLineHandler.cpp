#include "stdafx.h"
#include "MeasureVisibilityLineHandler.h"

using namespace gEarthPack;
using namespace osgEarth;
using namespace osgEarth::Util;
using namespace osgEarth::Symbology;
using namespace osgEarth::Features;
using namespace osgEarth::Annotation;

MeasureVisibilityLineHandler::MeasureVisibilityLineHandler(osgEarth::MapNode* mapNode):MeasureBaseHandler(mapNode)
{
	setMapNode(mapNode);
}


MeasureVisibilityLineHandler::~MeasureVisibilityLineHandler()
{

}

void MeasureVisibilityLineHandler::rebuild()
{
	if (_lineofsightnode.valid())
	{
		_root->removeChild(_lineofsightnode.get());
		_lineofsightnode = 0L;
	}

	if (!getMapNode())
		return;

	if (getMapNode()->getMapSRS()->isProjected())
	{
		OE_WARN << "Sorry, MeasureTool does not yet support projected maps" << std::endl;
		return;
	}

	_lineofsightnode = new osgEarth::Util::LinearLineOfSightNode(_mapNode.get());
	_root->addChild(_lineofsightnode.get());
}

void MeasureVisibilityLineHandler::clear()
{
	_lineofsightnode->setStart(osgEarth::GeoPoint());
	_lineofsightnode->setEnd(osgEarth::GeoPoint());
}
