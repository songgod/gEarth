#include "stdafx.h"
#include "MeasureVisibilityAreaHandler.h"

using namespace gEarthPack;
using namespace osgEarth;
using namespace osgEarth::Util;
using namespace osgEarth::Symbology;
using namespace osgEarth::Features;
using namespace osgEarth::Annotation;

MeasureVisibilityAreaHandler::MeasureVisibilityAreaHandler(osgEarth::MapNode* mapNode) :MeasureBaseHandler(mapNode)
{
	setMapNode(mapNode);
}


MeasureVisibilityAreaHandler::~MeasureVisibilityAreaHandler()
{

}

void MeasureVisibilityAreaHandler::rebuild()
{
	if (_radiaofsightnode.valid())
	{
		_root->removeChild(_radiaofsightnode.get());
		_radiaofsightnode = 0L;
	}

	if (!getMapNode())
		return;

	if (getMapNode()->getMapSRS()->isProjected())
	{
		OE_WARN << "Sorry, MeasureTool does not yet support projected maps" << std::endl;
		return;
	}

	_radiaofsightnode = new osgEarth::Util::RadialLineOfSightNode(_mapNode.get());
	_root->addChild(_radiaofsightnode.get());
}

void MeasureVisibilityAreaHandler::clear()
{

}
