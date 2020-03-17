#include "stdafx.h"
#include "oepAnimationPath.h"
#include "oepRender.h"
#include "Viewer.h"
#include "AnimationPathOptions.h"

using namespace gEarthPack;


oepAnimationPath::oepAnimationPath()
{
	bind(new osgEarth::AnimationPath::AnimationPathInfo());
	_controlpoints = gcnew oepControlPoints();
	init();
	_controlpoints->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepAnimationPath::OnControlPointsCollectionChanged);
}

void oepAnimationPath::PlayPath(oepAnimationPath^ path, oepRender^ render)
{
	if (render==nullptr || render->_viewer==NULL ||
		path== nullptr || path->ref() == NULL || path->ref()->animationpath() == NULL)
		return;
	render->_viewer->playPath(path->ref()->animationpath());
}

oepAnimationPath^ oepAnimationPath::From(String^ url)
{
	if (String::IsNullOrEmpty(url))
		return nullptr;
	osgEarth::AnimationPath::AnimationPathInfo* info = new osgEarth::AnimationPath::AnimationPathInfo();
	info->name() = Str2Std(System::IO::Path::GetFileNameWithoutExtension(url));
	info->url() = Str2Std(url);
	
	oepAnimationPath^ res = gcnew oepAnimationPath(info);
	return res;
}

bool oepAnimationPath::Save()
{
	if (_handle!=NULL && _handle->getValue()!=NULL && _handle->getValue()->animationpath()!=NULL && !_handle->getValue()->animationpath()->empty() && !String::IsNullOrEmpty(Url))
	{
		std::string url = Str2Std(Url);
		std::ofstream ofs(url);
		ofs.setf(std::ios::fixed, std::ios::floatfield);
		ofs.precision(15);
		_handle->getValue()->animationpath()->write(ofs);
		ofs.close();
		return true;
	}
	return false;
}

oepAnimationPath::oepAnimationPath(osgEarth::AnimationPath::AnimationPathInfo* info)
{
	bind(info);
	_controlpoints = gcnew oepControlPoints();
	init();
	_controlpoints->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepAnimationPath::OnControlPointsCollectionChanged);
}

void oepAnimationPath::init()
{
	osgEarth::AnimationPath::AnimationPathInfo* ap = ref();
	if (!ap || !ap->animationpath())
		return;

	osg::AnimationPath::TimeControlPointMap& tcpm = ap->animationpath()->getTimeControlPointMap();
	osg::AnimationPath::TimeControlPointMap::iterator iter = tcpm.begin();
	for (iter; iter != tcpm.end(); iter++)
	{
		oepControlPoint^ cp = gcnew oepControlPoint();
		cp->bind(&(iter->second),false);
		cp->Time = iter->first;
		_controlpoints->Add(cp);
	}
}

void oepAnimationPath::OnControlPointsCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e)
{
	osgEarth::AnimationPath::AnimationPathInfo* ap = ref();
	if (!ap || !ap->animationpath())
		return;

	osg::AnimationPath::TimeControlPointMap& tcpm = ap->animationpath()->getTimeControlPointMap();
	switch (e->Action)
	{
	case System::Collections::Specialized::NotifyCollectionChangedAction::Add:
	{
		if (e->NewItems != nullptr && e->NewItems->Count > 0)
		{
			for (int i = 0; i < e->NewItems->Count; i++)
			{
				oepControlPoint^ oepcp = dynamic_cast<oepControlPoint^>(e->NewItems[i]);
				if (oepcp != nullptr && oepcp->as<osg::AnimationPath::ControlPoint>() != NULL)
				{
					osg::AnimationPath::ControlPoint vp = *(oepcp->as<osg::AnimationPath::ControlPoint>());
					double time = oepcp->Time;
					tcpm[time] = vp;
					oepcp->bind(&(tcpm[time]),false);
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
				oepControlPoint^ oepcp = dynamic_cast<oepControlPoint^>(e->OldItems[i]);
				if (oepcp != nullptr)
				{
					tcpm.erase(oepcp->Time);
					oepcp->unbind();
				}
			}
		}
		break;
	}
	case System::Collections::Specialized::NotifyCollectionChangedAction::Replace:
	{
		if (e->NewItems->Count > 0 && e->NewStartingIndex >= 0 && e->NewStartingIndex < tcpm.size())
		{
			oepControlPoint^ oepcp = dynamic_cast<oepControlPoint^>(e->NewItems[0]);
			tcpm[oepcp->Time] = *(oepcp->val());
			oepcp->bind(&(tcpm[oepcp->Time]),false);
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
		tcpm.clear();
		break;
	}
	default:
		break;
	}
}

String^ oepAnimationPath::Name::get()
{
	osgEarth::AnimationPath::AnimationPathInfo *ap = ref();
	if (!ap)
		return "";
	return Str2Cli(ap->name());
}

void oepAnimationPath::Name::set(String^ v)
{
	osgEarth::AnimationPath::AnimationPathInfo *ap = ref();
	if (!ap)
		return;

	ap->name() = Str2Std(v);
	NotifyChanged("Name");
}

String^ oepAnimationPath::Url::get()
{
	osgEarth::AnimationPath::AnimationPathInfo *ap = ref();
	if (!ap)
		return "";
	return Str2Cli(ap->url());
}

void oepAnimationPath::Url::set(String^ v)
{
	osgEarth::AnimationPath::AnimationPathInfo *ap = ref();
	if (!ap)
		return;

	ap->url() = Str2Std(v);
	NotifyChanged("Url");
}

oepControlPoints^ oepAnimationPath::ControlPoints::get()
{
	return _controlpoints;
}

oepControlPoint::oepControlPoint() : _time(0.0)
{
	bind(new osg::AnimationPath::ControlPoint(),true);
}

oepControlPoint::oepControlPoint(osg::AnimationPath::ControlPoint& cp)
{
	bind(new osg::AnimationPath::ControlPoint(cp.getPosition(),cp.getRotation(),cp.getScale()),true);
}

oepControlPoint^ oepControlPoint::MakeControlPoint(oepRender^ render, double time)
{
	if (render == nullptr || render->_viewer==NULL || render->_viewer->getViewer()==NULL)
		return nullptr;
	const osg::Matrixd& m = render->_viewer->getViewer()->getCamera()->getInverseViewMatrix();
	osg::AnimationPath::ControlPoint cp(m.getTrans(), m.getRotate());
	oepControlPoint^ oepcp = gcnew oepControlPoint(cp);
	oepcp->Time = time;
	return oepcp;
}

double oepControlPoint::Time::get()
{
	return _time;
}

void oepControlPoint::Time::set(double v)
{
	_time = v;
}
