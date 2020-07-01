#include "stdafx.h"
#include "oepResource.h"

using namespace gEarthPack;
using namespace osgEarth::Symbology;


oepResource::oepResource()
{
	
}

void oepResource::binded()
{
	_tags = gcnew ObservableCollection<String ^>();
	const TagSet &tagset = ntResource()->tags();
	TagSet::const_iterator citer = tagset.begin();
	for (citer; citer != tagset.end(); ++citer)
	{
		_tags->Add(Str2Cli(*citer));
	}
	_tags->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &gEarthPack::oepResource::OnMTCollectionChanged);
}

void oepResource::unbinded()
{
	_tags->Clear();
}

void oepResource::OnMTCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e)
{
	switch (e->Action)
	{
	case System::Collections::Specialized::NotifyCollectionChangedAction::Add:
	{
		if (e->NewItems != nullptr && e->NewItems->Count > 0)
		{
			for (int i = 0; i < e->NewItems->Count; i++)
			{
				String^ tag = dynamic_cast<String^>(e->NewItems[i]);
				if (tag != nullptr)
				{
					ntResource()->addTag(Str2Std(tag));
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
				String^ tag = dynamic_cast<String^>(e->OldItems[i]);
				if (tag != nullptr)
				{
					ntResource()->removeTag(Str2Std(tag));
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
		TagSet tagset = ntResource()->tags();
		TagSet::const_iterator citer = tagset.begin();
		for (citer; citer != tagset.end(); ++citer)
		{
			ntResource()->removeTag(*citer);
		}
		break;
	}
	default:
		break;
	}
}

String^ oepResource::Name::get()
{
	return Str2Cli(ntResource()->getName());
}

void oepResource::Name::set(String^ p)
{
	ntResource()->setName(Str2Std(p));
	NotifyChanged("Name");
}

ObservableCollection<String^>^ oepResource::Tags::get()
{
	return _tags;
}

void oepResource::Tags::set(ObservableCollection<String^>^ p)
{
	TagSet tagset = ntResource()->tags();
	TagSet::const_iterator citer = tagset.begin();
	for (citer; citer != tagset.end(); ++citer)
	{
		ntResource()->removeTag(*citer);
	}

	_tags = p;
	for each (String^ tag in p)
	{
		ntResource()->addTag(Str2Std(tag));
	}
	_tags->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &gEarthPack::oepResource::OnMTCollectionChanged);
	NotifyChanged("Tags");
}
