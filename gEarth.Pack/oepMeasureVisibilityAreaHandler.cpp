#include "stdafx.h"
#include "MeasureVisibilityAreaHandler.h"
#include "oepMeasureVisibilityAreaHandler.h"
#include "oepHandleMapManager.h"

using namespace gEarthPack;

oepMeasureVisibilityAreaHandler::oepMeasureVisibilityAreaHandler()
{
}


void oepMeasureVisibilityAreaHandler::bind(osgEarth::MapNode* pMapNode)
{
	MeasureVisibilityAreaHandler* mth = new MeasureVisibilityAreaHandler();
	mth->setMapNode(pMapNode);
	bind(mth);
	oepHandleMapManager::registerHandle(mth, this);

	mth->setIntersectionMask(0x1);

	_nodemask = pMapNode->getNodeMask();
	pMapNode->setNodeMask(0x1);
}

void oepMeasureVisibilityAreaHandler::unbind(osgEarth::MapNode* pMapNode)
{
	MeasureVisibilityAreaHandler* handle = as<MeasureVisibilityAreaHandler>();
	if (!handle)
		return;

	if (handle->getMapNode())
	{
		handle->getMapNode()->setNodeMask(_nodemask);
	}
	handle->setMapNode(NULL);
	oepHandleMapManager::unRegisterHandle(handle);
}