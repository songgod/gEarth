#include "stdafx.h"
#include "oepMap.h"
#include "Handle.h"
#include <osgDB\ReadFile>
#include <osgDB\WriteFile>
#include <msclr\marshal_cppstd.h>  
#include "oepLayerFactory.h"
#include "oepExtensionFactory.h"

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
	InitLayers();
	InitExtensions();
	return true;
}

void gEarthPack::oepMap::InitLayers()
{
	osgEarth::Map* pMap = getMap();
	if (pMap == NULL)
		return;

	_layers->CollectionChanged -= gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &gEarthPack::oepMap::OnLayersCollectionChanged);
	for (unsigned int i = 0; i < pMap->getNumLayers(); i++)
	{
		osgEarth::Layer* pLayer = pMap->getLayerAt(i);
		std::string type = pLayer->options().getConfig().key();
		oepLayer^ layer = oepLayerFactory::creatorLayer(marshal_as<String^>(type), IntPtr(pLayer));
		if(layer==nullptr)
			continue;
		
		_layers->Add(layer);
	}
	_layers->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &gEarthPack::oepMap::OnLayersCollectionChanged);
}

void gEarthPack::oepMap::InitExtensions()
{
	osgEarth::MapNode* pMapNode = getMapNode();
	if (pMapNode == NULL)
		return;
	_extensions->CollectionChanged -= gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &gEarthPack::oepMap::OnExtensionsCollectionChanged);
	const std::vector<osg::ref_ptr<osgEarth::Extension>>&extensions = pMapNode->getExtensions();
	for (unsigned int i = 0; i < extensions.size(); i++)
	{
		osgEarth::Extension* oeextension = extensions[i];
		std::string type = oeextension->getConfigKey();
		oepExtension^ extension = oepExtensionFactory::creatorExtenson(marshal_as<String^>(type), IntPtr(oeextension));
		if (extension == nullptr)
			continue;

		_extensions->Add(extension);
	}
	_extensions->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &gEarthPack::oepMap::OnExtensionsCollectionChanged);
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
		if (e->NewItems != nullptr && e->NewItems->Count > 0)
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
		}
		break;
	}
	case System::Collections::Specialized::NotifyCollectionChangedAction::Remove:
	{
		if (e->OldItems != nullptr && e->OldItems->Count > 0)
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
		map->beginUpdate();
		osgEarth::Layer* layer = map->getLayerAt(e->OldStartingIndex);
		map->moveLayer(layer, e->NewStartingIndex);
		map->endUpdate();
		break;
	}
	case System::Collections::Specialized::NotifyCollectionChangedAction::Reset:
	{
		map->beginUpdate();
		map->clear();
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
		if (e->NewItems != nullptr && e->NewItems->Count > 0)
		{
			for (int i = 0; i < e->NewItems->Count; i++)
			{
				oepExtension^ ext = dynamic_cast<oepExtension^>(e->NewItems[i]);
				if (ext != nullptr && ext->asoeExtension())
				{
					mapnode->addExtension(ext->asoeExtension());
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
				oepExtension^ ext = dynamic_cast<oepExtension^>(e->NewItems[i]);
				if (ext != nullptr && ext->asoeExtension())
				{
					mapnode->removeExtension(ext->asoeExtension());
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
		mapnode->clearExtensions();
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

gEarthPack::oepLayers^ gEarthPack::oepMap::Layers::get()
{
	return _layers;
}

String^ gEarthPack::oepMap::Name::get()
{
	osgEarth::Map* pmap = getMap();
	if (!pmap)
		return "";
	return marshal_as<String^>(pmap->getName());
}

void gEarthPack::oepMap::Name::set(String^ v)
{
	osgEarth::Map* pmap = getMap();
	if (!pmap)
		return;
	pmap->setName(marshal_as<std::string>(v));
	NotifyChanged("Name");
}