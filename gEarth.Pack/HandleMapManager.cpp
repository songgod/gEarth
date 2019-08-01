#include "stdafx.h"
#include "HandleMapManager.h"

using namespace gEarthPack;

static gEarthPack::HandleMapManager::HandleMapManager()
{
	_handlemap = gcnew HandleMap();
}

void gEarthPack::HandleMapManager::registerHandle(void* p, Object^ obj)
{
	if (obj == nullptr || p == NULL)
		return;

	_handlemap[IntPtr(p)] = obj;
}

void gEarthPack::HandleMapManager::unRegisterHandle(void* p)
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

Object^ gEarthPack::HandleMapManager::getHandle(void* p)
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

void gEarthPack::HandleMapManager::unRegisterHandle(Object^ obj)
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
