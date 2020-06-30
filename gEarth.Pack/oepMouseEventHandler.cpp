#include "stdafx.h"
#include "oepMouseEventHandler.h"
#include "MouseEventHandler.h"
#include "oepHandleMapManager.h"

using namespace gEarthPack;

namespace gEarthPack
{
	class MouseEventCallback : public MouseEventHandler::MouseCallback
	{
	public:
		MouseEventCallback()
		{
		}

	public:

		virtual void onMouseDown(MouseEventHandler* sender, const osg::Vec3d& coords, int keybutton)
		{
			oepMouseEventHandler^ handle = oepHandleMapManager::getHandle<oepMouseEventHandler>(sender);
			if (handle == nullptr)
				return;

			handle->FireMouseDown(oepVec3f(coords.y(), coords.x(), coords.z()), keybutton);
		}

		virtual void onMouseUp(MouseEventHandler* sender, const osg::Vec3d& coords, int keybutton)
		{
			oepMouseEventHandler^ handle = oepHandleMapManager::getHandle<oepMouseEventHandler>(sender);
			if (handle == nullptr)
				return;

			handle->FireMouseUp(oepVec3f(coords.y(), coords.x(), coords.z()), keybutton);
		}

		virtual void onMouseMove(MouseEventHandler* sender, const osg::Vec3d& coords, int keybutton)
		{
			oepMouseEventHandler^ handle = oepHandleMapManager::getHandle<oepMouseEventHandler>(sender);
			if (handle == nullptr)
				return;

			handle->FireMouseMove(oepVec3f(coords.y(), coords.x(), coords.z()), keybutton);
		}

		virtual void onMouseDrag(MouseEventHandler* sender, const osg::Vec3d& coords, int keybutton)
		{
			oepMouseEventHandler^ handle = oepHandleMapManager::getHandle<oepMouseEventHandler>(sender);
			if (handle == nullptr)
				return;

			handle->FireMouseDrag(oepVec3f(coords.y(), coords.x(), coords.z()), keybutton);
		}

		virtual void onMouseDoubleClick(MouseEventHandler* sender, const osg::Vec3d& coords, int keybutton)
		{
			oepMouseEventHandler^ handle = oepHandleMapManager::getHandle<oepMouseEventHandler>(sender);
			if (handle == nullptr)
				return;

			handle->FireMouseDown(oepVec3f(coords.y(), coords.x(), coords.z()), keybutton);
		}
	};
}

oepMouseEventHandler::oepMouseEventHandler()
{
}

void oepMouseEventHandler::FireMouseDown(oepVec3f p, int keybutton)
{
	OnMouseDown(this, p, keybutton);
}

void oepMouseEventHandler::FireMouseUp(oepVec3f p, int keybutton)
{
	OnMouseUp(this, p, keybutton);
}

void oepMouseEventHandler::FireMouseMove(oepVec3f p, int keybutton)
{
	OnMouseMove(this, p, keybutton);
}

void oepMouseEventHandler::FireMouseDrag(oepVec3f p, int keybutton)
{
	OnMouseDrag(this, p, keybutton);
}

void oepMouseEventHandler::FireMouseDoubleClick(oepVec3f p, int keybutton)
{
	OnMouseDoubleClick(this, p, keybutton);
}

void gEarthPack::oepMouseEventHandler::bind(osgEarth::MapNode* pMapNode)
{
	MouseEventHandler* mth = new MouseEventHandler();
	mth->setMapNode(pMapNode);
	mth->getMouseCallbacks().push_back(new MouseEventCallback());
	bind(mth);
	oepHandleMapManager::registerHandle(mth, this);
}

void gEarthPack::oepMouseEventHandler::unbind(osgEarth::MapNode* pMapNode)
{
	MouseEventHandler* handle = as<MouseEventHandler>();
	if (!handle)
		return;
	handle->setMapNode(NULL);
	oepHandleMapManager::unRegisterHandle(handle);
}
