// This is the main DLL file.

#include "stdafx.h"

#include "oepRender.h"
#include "viewer.h"
#include <string>


using namespace gEarthPack;

oepRender::oepRender():_viewer(NULL)
{
	_handlers = gcnew oepEventHandlers();
	_handlers->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepRender::OnHandlersCollectionChanged);
}

void oepRender::Start(IntPtr hwnd)
{
	if (_viewer)
		return;

	HWND h = (HWND)hwnd.ToPointer();
	_viewer = new Viewer(h);
	_viewer->init();
	_viewer->start();

}

void oepRender::End()
{
	if (_viewer)
	{
		delete _viewer;
		_viewer = NULL;
	}
}

bool oepRender::Open(oepMap^ map)
{
	osgEarth::MapNode* pMapNode = map->getMapNode();
	if (!pMapNode)
		return false;

	_viewer->open(pMapNode);
	return true;
}


void oepRender::OnHandlersCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e)
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
					if(oepeh->ntEventHandler())
						_viewer->getViewer()->addEventHandler(oepeh->ntEventHandler());
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
				if (oepeh != nullptr && oepeh->ntEventHandler() != NULL)
				{
					_viewer->pause();
					oepeh->unbind(_viewer->getMapNode());
					if (oepeh->ntEventHandler())
					{
						if(!oepeh->Keep)
							_viewer->getViewer()->removeEventHandler(oepeh->ntEventHandler());
					}
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

oepViewpoint^ oepRender::Viewpoint::get()
{
	osgEarth::Viewpoint vp = _viewer->getViewpoint();
	return gcnew oepViewpoint(vp);
}

void oepRender::Viewpoint::set(oepViewpoint^ v)
{
	if (v == nullptr || v->ntViewpoint() == NULL)
		return;
	_viewer->flyto(*(v->ntViewpoint()));
	NotifyChanged("Viewpoint");
}

oepEventHandlers^ oepRender::Handlers::get()
{
	return _handlers;
}
