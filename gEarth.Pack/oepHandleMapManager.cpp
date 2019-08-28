#include "stdafx.h"
#include "oepHandleMapManager.h"

using namespace gEarthPack;

static oepHandleMapManager::oepHandleMapManager()
{
	_handlemap = gcnew HandleMap();
}

void oepHandleMapManager::registerHandle(void* p, Object^ obj)
{
	if (obj == nullptr || p == NULL)
		return;

	_handlemap[IntPtr(p)] = obj;
}

void oepHandleMapManager::unRegisterHandle(void* p)
{
	if (p == NULL)
		return;

	for each (IntPtr key in _handlemap->Keys)
	{
		if (key.ToPointer() == p)
		{
			_handlemap->Remove(key);
			break;
		}
	}
}

Object^ oepHandleMapManager::getHandle(void* p)
{
	if (p == NULL)
		return nullptr;


	for each (IntPtr key in _handlemap->Keys)
	{
		if (key.ToPointer() == p)
		{
			return _handlemap[key];
		}
	}
	return nullptr;
}

void oepHandleMapManager::unRegisterHandle(Object^ obj)
{
	if (obj == nullptr)
		return;

	typedef KeyValuePair<IntPtr, Object^> HandlePair;
	for each (HandlePair p in _handlemap)
	{
		if (p.Value == obj)
		{
			_handlemap->Remove(p.Key);
			break;
		}
	}
}
