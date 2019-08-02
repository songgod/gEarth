// This is the main DLL file.

#include "stdafx.h"

#include "Render.h"

#include <string>  
#include <msclr\marshal_cppstd.h>  
#include "HandleMapManager.h"
#include "MouseCoordHandler.h"

using namespace msclr::interop;
using namespace gEarthPack;

namespace
{
	class MouseMoveCallback : public MouseCoordHandler::MouseMoveCallback
	{
	public:

		MouseMoveCallback()
		{

		}

	public:

		virtual void update(MouseCoordHandler* sender, const osg::Vec3& coords)
		{
			Render^ render = HandleMapManager::getHandle<Render>(sender);
			if (render == nullptr)
				return;

			render->FireMoveEvent(oepVec3f(coords.y(), coords.x(), coords.z()));
		}
	};
}

Render::Render():_viewer(NULL)
{
	_handlers = gcnew oepEventHandlers();
	_handlers->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &Render::OnHandlersCollectionChanged);
}

void Render::Start(IntPtr hwnd)
{
	if (_viewer)
		return;

	HWND h = (HWND)hwnd.ToPointer();
	_viewer = new Viewer(h);
	_viewer->init();
	InitEvents();
	_viewer->start();

}

void Render::End()
{
	HandleMapManager::unRegisterHandle(_viewer->getMouseCoordHandler());
	if (_viewer)
	{
		delete _viewer;
		_viewer = NULL;
	}
}

bool Render::Open(oepMap^ map)
{
	osgEarth::MapNode* pMapNode = map->getMapNode();
	if (!pMapNode)
		return false;

	_viewer->open(pMapNode);
	return true;
}

void Render::InitEvents()
{
	HandleMapManager::registerHandle(_viewer->getMouseCoordHandler(), this);
	MouseMoveCallback* cb = new MouseMoveCallback();
	_viewer->getMouseCoordHandler()->addMoveCallback(cb);
}

void Render::OnHandlersCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e)
{
	if (!_viewer || !_viewer->getMapNode())
	{
		throw gcnew Exception("MapNode is NULL");
		return;
	}
	switch (e->Action)
	{
	case System::Collections::Specialized::NotifyCollectionChangedAction::Add:
	{
		if (e->NewItems != nullptr && e->NewItems->Count > 0)
		{
			for (int i = 0; i < e->NewItems->Count; i++)
			{
				oepEventHandler^ oepeh = dynamic_cast<oepEventHandler^>(e->NewItems[i]);
				if (oepeh != nullptr)
				{
					_viewer->pause();
					oepeh->bind(_viewer->getMapNode());
					if(oepeh->asosgEventHandler())
						_viewer->getViewer()->addEventHandler(oepeh->asosgEventHandler());
					else
						throw gcnew Exception("oepEventHandler's internal handler is NULL");
					_viewer->resume();
				}
			}
		}
		break;
	}
	case System::Collections::Specialized::NotifyCollectionChangedAction::Remove:
	{
		if (e->OldItems != nullptr && e->OldItems->Count > 0)
		{
			for (int i = 0; i < e->OldItems->Count; i++)
			{
				oepEventHandler^ oepeh = dynamic_cast<oepEventHandler^>(e->OldItems[i]);
				if (oepeh != nullptr && oepeh->asosgEventHandler() != NULL)
				{
					_viewer->pause();
					oepeh->unbind(_viewer->getMapNode());
					if (oepeh->asosgEventHandler())
						_viewer->getViewer()->removeEventHandler(oepeh->asosgEventHandler());
					else
						throw gcnew Exception("oepEventHandler's internal handler is NULL");
					_viewer->resume();
				}
			}
		}
		break;
	}
	case System::Collections::Specialized::NotifyCollectionChangedAction::Replace:
	{
		throw gcnew NotImplementedException();
		break;
	}
	case System::Collections::Specialized::NotifyCollectionChangedAction::Move:
	{
		throw gcnew NotImplementedException();
		break;
	}
	case System::Collections::Specialized::NotifyCollectionChangedAction::Reset:
	{
		throw gcnew NotImplementedException();
		break;
	}
	default:
		break;
	}
}

void Render::FireMoveEvent(oepVec3f p)
{
	OnMouseMove(this, p);
}

oepViewpoint^ Render::Viewpoint::get()
{
	osgEarth::Viewpoint vp = _viewer->getViewpoint();
	return gcnew oepViewpoint(vp);
}

void Render::Viewpoint::set(oepViewpoint^ v)
{
	if (v == nullptr || v->asoeViewpoint() == NULL)
		return;
	_viewer->flyto(*(v->asoeViewpoint()));
	NotifyChanged("Viewpoint");
}

oepEventHandlers^ Render::Handlers::get()
{
	return _handlers;
}
