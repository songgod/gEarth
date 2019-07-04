#include "stdafx.h"
#include "oepImageLayer.h"
using namespace gEarthPack;

oepImageLayer::oepImageLayer(oepTileSource^ source)
	:oepTerrainLayer(source)
{
	if (source != nullptr && source->getoeConfigOptions() != NULL)
		_handle->setValue(new osgEarth::ImageLayer(*(source->getoeConfigOptions())));
	else
		_handle->setValue(new osgEarth::ImageLayer());

	_colorfilters = gcnew oepColorFilters();
	_colorfilters->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &gEarthPack::oepImageLayer::OnColorFiltersCollectionChanged);
}

oepImageLayer::oepImageLayer(osgEarth::ImageLayer* layer)
{
	_handle->setValue(layer);
}

osgEarth::ImageLayer* gEarthPack::oepImageLayer::asoeImageLayer()
{
	return dynamic_cast<osgEarth::ImageLayer*>(_handle->getValue());
}

gEarthPack::oepColorFilters^ gEarthPack::oepImageLayer::ColorFilters::get()
{
	return _colorfilters;
}

void gEarthPack::oepImageLayer::OnColorFiltersCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e)
{
	osgEarth::ImageLayer* pLayer = asoeImageLayer();
	if (!pLayer)
		return;
	switch (e->Action)
	{
	case System::Collections::Specialized::NotifyCollectionChangedAction::Add:
	{
		if (e->NewItems != nullptr && e->NewItems->Count>0)
		{
			for (int i = 0; i < e->NewItems->Count; i++)
			{
				oepColorFilter^ cf = dynamic_cast<oepColorFilter^>(e->NewItems[i]);
				if (cf != nullptr && cf->asoeColorFilter() != NULL)
				{
					pLayer->addColorFilter(cf->asoeColorFilter());
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
				oepColorFilter^ cf = dynamic_cast<oepColorFilter^>(e->OldItems[i]);
				if (cf != nullptr && cf->asoeColorFilter() != NULL)
				{
					pLayer->removeColorFilter(cf->asoeColorFilter());
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
		osgEarth::ColorFilterChain cfc = pLayer->getColorFilters();
		for (size_t i = 0; i < cfc.size(); i++)
		{
			pLayer->removeColorFilter(cfc[i]);
		}
		break;
	}
	default:
		break;
	}
}
