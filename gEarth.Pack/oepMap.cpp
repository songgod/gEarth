#include "stdafx.h"
#include "oepMap.h"
#include "Handle.h"
#include <osgDB\ReadFile>
#include <osgDB\WriteFile>
#include <msclr\marshal_cppstd.h>  

using namespace msclr::interop;

gEarthPack::oepMap::oepMap()
{
	_handle = new MapHandle(new osgEarth::MapNode(new osgEarth::Map()));
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

bool gEarthPack::oepMap::load(String^ url)
{
	if (!Url->Empty)
		return false;

	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(marshal_as<std::string>(url));
	if (!node)
		return false;

	osgEarth::MapNode* mapnode = osgEarth::MapNode::get(node);
	if (!mapnode)
		return false;

	delete _handle;
	_handle = new MapHandle(mapnode);

	Url = url;
	_layers->init(mapnode->getMap());
	return true;
}

bool gEarthPack::oepMap::save()
{
	return osgDB::writeNodeFile(*_handle->getValue(), marshal_as<std::string>(Url));
}

bool gEarthPack::oepMap::saveAs(String^ url)
{
	if (osgDB::writeNodeFile(*_handle->getValue(), marshal_as<std::string>(url)))
	{
		Url = url;
		return true;
	}
	return false;
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
	osgEarth::MapNode* pMapNode = _handle->getValue();
	if (pMapNode) return pMapNode->getMap();
	return NULL;
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

String^ gEarthPack::oepMap::Url::get()
{
	return _url;
}

void gEarthPack::oepMap::Url::set(String^ url)
{
	_url = url;
	NotifyChanged("Url");
}
