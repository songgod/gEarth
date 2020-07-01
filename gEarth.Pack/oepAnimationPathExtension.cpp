#include "stdafx.h"
#include "oepAnimationPathExtension.h"
#include "AnimationPathOptions.h"
#include "oepExtensionFactory.h"

using namespace gEarthPack;

oepAnimationPathExtension::oepAnimationPathExtension()
{
	osgEarth::AnimationPath::AnimationPathOptions options;
	osgEarth::Config conf = options.getConfig();
	osgEarth::Extension* extension = oepExtensionFactory::createoeExtension(conf);
	if (!extension) throw gcnew Exception("Invalid viewpoints extension");
	bind(extension);
	_animationpaths = gcnew oepAnimationPaths();
	init();
	_animationpaths->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepAnimationPathExtension::OnAnimationPathCollectionChanged);
}

void oepAnimationPathExtension::init()
{
	osgEarth::AnimationPath::AnimationPathOptions* vo = as<osgEarth::AnimationPath::AnimationPathOptions>();
	if (!vo)
		return;

	osgEarth::AnimationPath::AnimationPathInfos &aps = vo->animationpaths();
	for (size_t i = 0; i < aps.size(); i++)
	{
		oepAnimationPath^ ap = gcnew oepAnimationPath(aps[i]);
		_animationpaths->Add(ap);
	}
}

void oepAnimationPathExtension::OnAnimationPathCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e)
{
	osgEarth::AnimationPath::AnimationPathOptions* vo = as<osgEarth::AnimationPath::AnimationPathOptions>();
	if (!vo)
		return;
	osgEarth::AnimationPath::AnimationPathInfos& aps = vo->animationpaths();
	switch (e->Action)
	{
	case System::Collections::Specialized::NotifyCollectionChangedAction::Add:
	{
		if (e->NewItems != nullptr && e->NewItems->Count > 0)
		{
			for (int i = 0; i < e->NewItems->Count; i++)
			{
				oepAnimationPath^ oepap = dynamic_cast<oepAnimationPath^>(e->NewItems[i]);
				if (oepap != nullptr && oepap->ntAnimationPathInfo() != NULL)
				{
					osgEarth::AnimationPath::AnimationPathInfo *ap = oepap->ntAnimationPathInfo();
					aps.push_back(ap);
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
				oepAnimationPath^ oepap = dynamic_cast<oepAnimationPath^>(e->OldItems[i]);
				if (oepap != nullptr && oepap->ntAnimationPathInfo() != NULL)
				{
					osgEarth::AnimationPath::AnimationPathInfo *ap = oepap->ntAnimationPathInfo();
					osgEarth::AnimationPath::AnimationPathInfos::iterator iter = aps.begin();
					for (iter; iter != aps.end(); ++iter)
					{
						if ((*iter).get() == ap)
						{
							aps.erase(iter);
							break;
						}
					}
				}
			}
		}
		break;
	}
	case System::Collections::Specialized::NotifyCollectionChangedAction::Replace:
	{
		if (e->NewItems->Count > 0 && e->NewStartingIndex >= 0 && e->NewStartingIndex < aps.size())
		{
			oepAnimationPath^ oepap = dynamic_cast<oepAnimationPath^>(e->NewItems[0]);
			aps[e->NewStartingIndex] = oepap->ntAnimationPathInfo();
		}
		break;
	}
	case System::Collections::Specialized::NotifyCollectionChangedAction::Move:
	{
		throw gcnew NotImplementedException();
		break;
	}
	case System::Collections::Specialized::NotifyCollectionChangedAction::Reset:
	{
		aps.clear();
		break;
	}
	default:
		break;
	}
}

oepAnimationPathExtension::oepAnimationPathExtension(osgEarth::Extension* ext)
{
	bind(ext);
	_animationpaths = gcnew oepAnimationPaths();
	init();
	_animationpaths->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepAnimationPathExtension::OnAnimationPathCollectionChanged);
}

oepAnimationPaths^ oepAnimationPathExtension::AnimationPaths::get()
{
	return _animationpaths;
}
