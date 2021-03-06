#include "stdafx.h"
#include "oepMap.h"
#include "oepLayerFactory.h"
#include "oepExtensionFactory.h"


using namespace gEarthPack;

oepMap::oepMap()
{
	bind(new osgEarth::MapNode(new osgEarth::Map()));
	_layers = gcnew oepLayers();
	_layers->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepMap::OnLayersCollectionChanged);
	_extensions = gcnew oepExtensions();
	_extensions->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepMap::OnExtensionsCollectionChanged);
}

bool oepMap::load(String^ url)
{
	if (!Url->Empty)
		return false;

	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(Str2Std(url));
	if (!node)
		return false;

	osgEarth::MapNode* mapnode = osgEarth::MapNode::get(node);
	if (!mapnode)
		return false;

	bind(mapnode);

	Url = url;
	InitLayers();
	InitExtensions();
	return true;
}

void oepMap::InitLayers()
{
	osgEarth::Map* pMap = getMap();
	if (pMap == NULL)
		return;

	_layers->CollectionChanged -= gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepMap::OnLayersCollectionChanged);
	for (unsigned int i = 0; i < pMap->getNumLayers(); i++)
	{
		osgEarth::Layer* pLayer = pMap->getLayerAt(i);
		osgEarth::VisibleLayer* pVisibleLayer = dynamic_cast<osgEarth::VisibleLayer*>(pLayer);
		if(!pVisibleLayer)
			continue;
		std::string type = pLayer->options().getConfig().key();
		oepLayer^ layer = oepLayerFactory::creatorLayer(Str2Cli(type), IntPtr(pLayer));
		if(layer==nullptr)
			continue;
		
		_layers->Add(layer);
	}
	_layers->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepMap::OnLayersCollectionChanged);
}

void oepMap::InitExtensions()
{
	osgEarth::MapNode* pMapNode = getMapNode();
	if (pMapNode == NULL)
		return;
	_extensions->CollectionChanged -= gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepMap::OnExtensionsCollectionChanged);
	const std::vector<osg::ref_ptr<osgEarth::Extension>>&extensions = pMapNode->getExtensions();
	for (unsigned int i = 0; i < extensions.size(); i++)
	{
		osgEarth::Extension* oeextension = extensions[i];
		std::string type = oeextension->getConfigKey();
		oepExtension^ extension = oepExtensionFactory::creatorExtenson(Str2Cli(type), IntPtr(oeextension));
		if (extension == nullptr)
			continue;

		_extensions->Add(extension);
	}
	_extensions->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepMap::OnExtensionsCollectionChanged);
}

bool oepMap::save()
{
	return osgDB::writeNodeFile(*getMapNode(), Str2Std(Url));
}

bool oepMap::saveAs(String^ url)
{
	if (osgDB::writeNodeFile(*getMapNode(), Str2Std(url)))
	{
		Url = url;
		return true;
	}
	return false;
}

osgEarth::Map * oepMap::getMap()
{
	osgEarth::MapNode* pMapNode = getMapNode();
	if (pMapNode) return pMapNode->getMap();
	return NULL;
}

osgEarth::MapNode* oepMap::getMapNode()
{
	return as<osgEarth::MapNode>();
}

oepExtensions^ oepMap::Extensions::get()
{
	return _extensions;
}

void oepMap::OnLayersCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e)
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
					map->addLayer(layer->as<osgEarth::Layer>());
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
					map->removeLayer(layer->as<osgEarth::Layer>());
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

void oepMap::OnExtensionsCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e)
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
				if (ext != nullptr && ext->as<osgEarth::Extension>())
				{
					mapnode->addExtension(ext->as<osgEarth::Extension>());
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
				if (ext != nullptr && ext->as<osgEarth::Extension>())
				{
					mapnode->removeExtension(ext->as<osgEarth::Extension>());
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

String^ oepMap::Url::get()
{
	return _url;
}

void oepMap::Url::set(String^ url)
{
	_url = url;
	NotifyChanged("Url");
}

oepLayers^ oepMap::Layers::get()
{
	return _layers;
}

String^ oepMap::Name::get()
{
	osgEarth::Map* pmap = getMap();
	if (!pmap)
		return "";
	return Str2Cli(pmap->getName());
}

void oepMap::Name::set(String^ v)
{
	osgEarth::Map* pmap = getMap();
	if (!pmap)
		return;
	pmap->setName(Str2Std(v));
	NotifyChanged("Name");
}