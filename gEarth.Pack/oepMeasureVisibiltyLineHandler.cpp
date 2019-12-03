#include "stdafx.h"
#include "oepMeasureVisibiltyLineHandler.h"
#include "MeasureVisibilityLineHandler.h"
#include "oepHandleMapManager.h"

using namespace gEarthPack;

oepMeasureVisibiltyLineHandler::oepMeasureVisibiltyLineHandler()
{
}

void oepMeasureVisibiltyLineHandler::bind(osgEarth::MapNode* pMapNode)
{
	MeasureVisibilityLineHandler* mth = new MeasureVisibilityLineHandler(pMapNode);
	bind(mth);
	oepHandleMapManager::registerHandle(mth, this);

	mth->setIntersectionMask(0x1);

	_nodemask = pMapNode->getNodeMask();
	pMapNode->setNodeMask(0x1);
}

void oepMeasureVisibiltyLineHandler::unbind(osgEarth::MapNode* pMapNode)
{
	MeasureVisibilityLineHandler* handle = as<MeasureVisibilityLineHandler>();
	if (!handle)
		return;

	if (handle->getMapNode())
	{
		handle->getMapNode()->setNodeMask(_nodemask);
	}
	handle->setMapNode(NULL);
	oepHandleMapManager::unRegisterHandle(handle);
}