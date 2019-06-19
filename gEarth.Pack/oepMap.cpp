#include "stdafx.h"
#include "oepMap.h"
#include "Handle.h"

gEarthPack::oepMap::oepMap()
{
	_handle = new MapHandle(new osgEarth::Map());
	_layers = gcnew oepLayers();
	_layers->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &gEarthPack::oepMap::OnCollectionChanged);
}

gEarthPack::oepMap::~oepMap()
{
	quit();
}

gEarthPack::oepMap::!oepMap()
{
	quit();
}

void gEarthPack::oepMap::quit()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

osgEarth::Map * gEarthPack::oepMap::getMap()
{
	return _handle->getValue();
}

gEarthPack::oepLayers^ gEarthPack::oepMap::Layers::get()
{
	return _layers;
}

void gEarthPack::oepMap::OnCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e)
{
	osgEarth::Map* map = getMap();
	if (!map)
		return;
	switch (e->Action)
	{
	case System::Collections::Specialized::NotifyCollectionChangedAction::Add:
	{
		for (int i = 0; i < e->NewItems->Count; i++)
		{
			oepLayer^ layer = dynamic_cast<oepLayer^>(e->NewItems[i]);
			if (layer != nullptr)
				map->addLayer(layer->asoeLayer());
		}
		break;
	}
	case System::Collections::Specialized::NotifyCollectionChangedAction::Remove:
	{
		for (int i = 0; i < e->OldItems->Count; i++)
		{
			oepLayer^ layer = dynamic_cast<oepLayer^>(e->OldItems[i]);
			if (layer != nullptr)
				map->removeLayer(layer->asoeLayer());
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
		osgEarth::Layer* layer = map->getLayerAt(e->OldStartingIndex);
		map->moveLayer(layer, e->NewStartingIndex);
		break;
	}
	case System::Collections::Specialized::NotifyCollectionChangedAction::Reset:
	{
		for (int i = 0; i < e->OldItems->Count; i++)
		{
			oepLayer^ layer = dynamic_cast<oepLayer^>(e->OldItems[i]);
			if (layer != nullptr)
				map->removeLayer(layer->asoeLayer());
		}
		break;
	}
	default:
		break;
	}
}
