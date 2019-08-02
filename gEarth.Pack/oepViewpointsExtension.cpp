#include "stdafx.h"
#include "oepViewpointsExtension.h"
#include "oepExtensionFactory.h"

using namespace gEarthPack;

oepViewpointsExtension::oepViewpointsExtension()
{
	osgEarth::Viewpoints::ViewpointsOptions options;
	osgEarth::Config conf = options.getConfig();
	osgEarth::Extension* extension = oepExtensionFactory::createoeExtension(conf);
	if (!extension) throw gcnew Exception("Invalid viewpoints extension");
	_handle = new ExtensionHandle(extension);
	_viewpoints = gcnew oepViewPoints();
	init();
	_viewpoints->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepViewpointsExtension::OnViewpointsCollectionChanged);
}

oepViewpointsExtension::oepViewpointsExtension(osgEarth::Extension* ext)
{
	_handle = new ExtensionHandle(ext);
	_viewpoints = gcnew oepViewPoints();
	init();
	_viewpoints->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepViewpointsExtension::OnViewpointsCollectionChanged);
}

osgEarth::Viewpoints::ViewpointsOptions* oepViewpointsExtension::getoeViewpointsOptions()
{
	if (!_handle)
		return NULL;
	return dynamic_cast<osgEarth::Viewpoints::ViewpointsOptions*>(_handle->getValue());
}

void oepViewpointsExtension::init()
{
	osgEarth::Viewpoints::ViewpointsOptions* vo = getoeViewpointsOptions();
	if (!vo)
		return;

	std::vector<osgEarth::Viewpoint> &vps = vo->viewpoints();
	for (size_t i = 0; i < vps.size(); i++)
	{
		oepViewpoint^ vp = gcnew oepViewpoint();
		vp->setHandle(&vps[i]);
		_viewpoints->Add(vp);
	}
}

void oepViewpointsExtension::OnViewpointsCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e)
{
	osgEarth::Viewpoints::ViewpointsOptions* vo = getoeViewpointsOptions();
	if (!vo)
		return;
	switch (e->Action)
	{
	case System::Collections::Specialized::NotifyCollectionChangedAction::Add:
	{
		if (e->NewItems != nullptr && e->NewItems->Count > 0)
		{
			for (int i = 0; i < e->NewItems->Count; i++)
			{
				oepViewpoint^ oepvp = dynamic_cast<oepViewpoint^>(e->NewItems[i]);
				if (oepvp != nullptr && oepvp->asoeViewpoint()!=NULL)
				{
					osgEarth::Viewpoint vp = *(oepvp->asoeViewpoint());
					std::vector<osgEarth::Viewpoint>& vps = vo->viewpoints();
					vps.push_back(vp);
					oepvp->setHandle(&(vps[vps.size() - 1]));
				}
			}
		}
		break;
	}
	case System::Collections::Specialized::NotifyCollectionChangedAction::Remove:
	{
		oepViewPoints^ oepvps = dynamic_cast<oepViewPoints^>(sender);
		std::vector<osgEarth::Viewpoint>& vps = vo->viewpoints();
		if (oepvps!=nullptr && e->OldItems != nullptr && e->OldItems->Count > 0)
		{
			for (int i = 0; i < e->OldItems->Count; i++)
			{
				oepViewpoint^ oepvp = dynamic_cast<oepViewpoint^>(e->OldItems[i]);
				if (oepvp != nullptr && oepvp->asoeViewpoint() != NULL)
				{
					int index = oepvps->IndexOf(oepvp);
					if (index >= 0 && index <= vps.size())
					{
						vps.erase(vps.begin() + index);
						oepvp->resetHandle();
					}
				}
			}
		}
		break;
	}
	case System::Collections::Specialized::NotifyCollectionChangedAction::Replace:
	{
		std::vector<osgEarth::Viewpoint>& vps = vo->viewpoints();
		if (e->NewItems->Count > 0 && e->NewStartingIndex >= 0 && e->NewStartingIndex<vps.size())
		{
			oepViewpoint^ oepvp = dynamic_cast<oepViewpoint^>(e->NewItems[0]);
			vps[e->NewStartingIndex] = *(oepvp->asoeViewpoint());
			oepvp->setHandle(&(vps[e->NewStartingIndex]));
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
		std::vector<osgEarth::Viewpoint>& vps = vo->viewpoints();
		vps.clear();
		break;
	}
	default:
		break;
	}
}

oepViewPoints^ oepViewpointsExtension::ViewPoints::get()
{
	return _viewpoints;
}
