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
	_layers->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &gEarthPack::oepMap::OnLayersCollectionChanged);
	_extensions = gcnew oepExtensions();
	_extensions->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &gEarthPack::oepMap::OnExtensionsCollectionChanged);
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
	_layers->CollectionChanged -= gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &gEarthPack::oepMap::OnLayersCollectionChanged);
	_layers->init(mapnode->getMap());
	_layers->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &gEarthPack::oepMap::OnLayersCollectionChanged);
	_extensions->CollectionChanged -= gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &gEarthPack::oepMap::OnExtensionsCollectionChanged);
	_extensions->init(mapnode->getMap());
	_extensions->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &gEarthPack::oepMap::OnExtensionsCollectionChanged);
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

osgEarth::MapNode* gEarthPack::oepMap::getMapNode()
{
	return _handle->getValue();
}

gEarthPack::oepLayers^ gEarthPack::oepMap::Layers::get()
{
	return _layers;
}

gEarthPack::oepExtensions^ gEarthPack::oepMap::Extensions::get()
{
	return _extensions;
}

void gEarthPack::oepMap::OnLayersCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e)
{
	osgEarth::Map* map = getMap();
	if (!map)
		return;
	switch (e->Action)
	{
	case System::Collections::Specialized::NotifyCollectionChangedAction::Add:
	{
		map->beginUpdate();
		for (int i = 0; i < e->NewItems->Count; i++)
		{
			oepLayer^ layer = dynamic_cast<oepLayer^>(e->NewItems[i]);
			if (layer != nullptr)
			{
				map->addLayer(layer->asoeLayer());
			}
		}
		map->endUpdate();
		break;
	}
	case System::Collections::Specialized::NotifyCollectionChangedAction::Remove:
	{
		map->beginUpdate();
		for (int i = 0; i < e->OldItems->Count; i++)
		{
			oepLayer^ layer = dynamic_cast<oepLayer^>(e->OldItems[i]);
			if (layer != nullptr)
			{
				map->removeLayer(layer->asoeLayer());
			}
		}
		map->endUpdate();
		break;
	}
	case System::Collections::Specialized::NotifyCollectionChangedAction::Replace:
	{
		throw gcnew NotImplementedException();
		break;
	}
	case System::Collections::Specialized::NotifyCollectionChangedAction::Move:
	{
		map->beginUpdate();
		osgEarth::Layer* layer = map->getLayerAt(e->OldStartingIndex);
		map->moveLayer(layer, e->NewStartingIndex);
		map->endUpdate();
		break;
	}
	case System::Collections::Specialized::NotifyCollectionChangedAction::Reset:
	{
		map->beginUpdate();
		for (int i = 0; i < e->OldItems->Count; i++)
		{
			oepLayer^ layer = dynamic_cast<oepLayer^>(e->OldItems[i]);
			if (layer != nullptr)
				map->removeLayer(layer->asoeLayer());
		}
		map->endUpdate();
		break;
	}
	default:
		break;
	}
}

void gEarthPack::oepMap::OnExtensionsCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e)
{
	osgEarth::MapNode* mapnode = getMapNode();
	if (!mapnode)
		return;
	switch (e->Action)
	{
	case System::Collections::Specialized::NotifyCollectionChangedAction::Add:
	{
		for (int i = 0; i < e->NewItems->Count; i++)
		{
			oepExtension^ ext = dynamic_cast<oepExtension^>(e->NewItems[i]);
			if (ext != nullptr && ext->getoeExtension())
			{
				mapnode->addExtension(ext->getoeExtension());
			}
		}
		break;
	}
	case System::Collections::Specialized::NotifyCollectionChangedAction::Remove:
	{
		for (int i = 0; i < e->OldItems->Count; i++)
		{
			oepExtension^ ext = dynamic_cast<oepExtension^>(e->NewItems[i]);
			if (ext != nullptr && ext->getoeExtension())
			{
				mapnode->removeExtension(ext->getoeExtension());
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
		for (int i = 0; i < e->OldItems->Count; i++)
		{
			oepExtension^ ext = dynamic_cast<oepExtension^>(e->NewItems[i]);
			if (ext != nullptr && ext->getoeExtension())
			{
				mapnode->removeExtension(ext->getoeExtension());
			}
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

