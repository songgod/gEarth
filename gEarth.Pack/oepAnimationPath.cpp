#include "stdafx.h"
#include "oepAnimationPath.h"
#include "oepRender.h"
#include "Viewer.h"
#include "AnimationPathOptions.h"

using namespace gEarthPack;
using namespace msclr::interop;

oepAnimationPath::oepAnimationPath()
{
	_handle = new AnimationPathInfoHandle(new osgEarth::AnimationPath::AnimationPathInfo());
	_controlpoints = gcnew oepControlPoints();
	init();
	_controlpoints->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepAnimationPath::OnControlPointsCollectionChanged);
}

oepAnimationPath::!oepAnimationPath()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

oepAnimationPath::~oepAnimationPath()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

void oepAnimationPath::PlayPath(oepAnimationPath^ path, oepRender^ render)
{
	if (render==nullptr || render->_viewer==NULL ||
		path== nullptr || path->asoeAnimationPathInfo() == NULL || path->asoeAnimationPathInfo()->animationpath() == NULL)
		return;
	render->_viewer->playPath(path->asoeAnimationPathInfo()->animationpath());
}

oepAnimationPath^ oepAnimationPath::From(String^ url)
{
	if (String::IsNullOrEmpty(url))
		return nullptr;
	osgEarth::AnimationPath::AnimationPathInfo* info = new osgEarth::AnimationPath::AnimationPathInfo();
	info->name() = marshal_as<std::string>(System::IO::Path::GetFileNameWithoutExtension(url));
	info->url() = marshal_as<std::string>(url);
	
	oepAnimationPath^ res = gcnew oepAnimationPath(info);
	return res;
}

bool oepAnimationPath::Save()
{
	if (_handle!=NULL && _handle->getValue()!=NULL && _handle->getValue()->animationpath()!=NULL && !_handle->getValue()->animationpath()->empty() && !String::IsNullOrEmpty(Url))
	{
		std::string url = marshal_as<std::string>(Url);
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
	_handle = new AnimationPathInfoHandle(info);
	_controlpoints = gcnew oepControlPoints();
	init();
	_controlpoints->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepAnimationPath::OnControlPointsCollectionChanged);
}

osgEarth::AnimationPath::AnimationPathInfo* oepAnimationPath::asoeAnimationPathInfo()
{
	return _handle != NULL ? _handle->getValue() : NULL;
}

void oepAnimationPath::init()
{
	osgEarth::AnimationPath::AnimationPathInfo* ap = asoeAnimationPathInfo();
	if (!ap || !ap->animationpath())
		return;

	osg::AnimationPath::TimeControlPointMap& tcpm = ap->animationpath()->getTimeControlPointMap();
	osg::AnimationPath::TimeControlPointMap::iterator iter = tcpm.begin();
	for (iter; iter != tcpm.end(); iter++)
	{
		oepControlPoint^ cp = gcnew oepControlPoint();
		cp->setHandle(&(iter->second));
		cp->Time = iter->first;
		_controlpoints->Add(cp);
	}
}

void oepAnimationPath::OnControlPointsCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e)
{
	osgEarth::AnimationPath::AnimationPathInfo* ap = asoeAnimationPathInfo();
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
				if (oepcp != nullptr && oepcp->asosgControlPoint() != NULL)
				{
					osg::AnimationPath::ControlPoint vp = *(oepcp->asosgControlPoint());
					double time = oepcp->Time;
					tcpm[time] = vp;
					oepcp->setHandle(&(tcpm[time]));
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
					oepcp->resetHandle();
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
			tcpm[oepcp->Time] = *(oepcp->asosgControlPoint());
			oepcp->setHandle(&(tcpm[oepcp->Time]));
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
	osgEarth::AnimationPath::AnimationPathInfo *ap = asoeAnimationPathInfo();
	if (!ap)
		return "";
	return marshal_as<String^>(ap->name());
}

void oepAnimationPath::Name::set(String^ v)
{
	osgEarth::AnimationPath::AnimationPathInfo *ap = asoeAnimationPathInfo();
	if (!ap)
		return;

	ap->name() = marshal_as<std::string>(v);
	NotifyChanged("Name");
}

String^ oepAnimationPath::Url::get()
{
	osgEarth::AnimationPath::AnimationPathInfo *ap = asoeAnimationPathInfo();
	if (!ap)
		return "";
	return marshal_as<String^>(ap->url());
}

void oepAnimationPath::Url::set(String^ v)
{
	osgEarth::AnimationPath::AnimationPathInfo *ap = asoeAnimationPathInfo();
	if (!ap)
		return;

	ap->url() = marshal_as<std::string>(v);
	NotifyChanged("Url");
}

oepControlPoints^ oepAnimationPath::ControlPoints::get()
{
	return _controlpoints;
}

oepControlPoint::oepControlPoint() : _handle(new osg::AnimationPath::ControlPoint()), _ownhandle(true),_time(0.0)
{

}

void oepControlPoint::setHandle(osg::AnimationPath::ControlPoint* cp)
{
	if (_handle != NULL && _ownhandle)
	{
		delete _handle;
		_handle = NULL;
	}
	_handle = cp;
	_ownhandle = false;
}

void oepControlPoint::resetHandle()
{
	if (_ownhandle)
		return;
	_handle = new osg::AnimationPath::ControlPoint();
	_ownhandle = true;
}

osg::AnimationPath::ControlPoint* oepControlPoint::asosgControlPoint()
{
	return _handle;
}

oepControlPoint::~oepControlPoint()
{
	if (_handle != NULL && _ownhandle)
	{
		delete _handle;
		_handle = NULL;
	}
}

oepControlPoint::!oepControlPoint()
{
	if (_handle != NULL && _ownhandle)
	{
		delete _handle;
		_handle = NULL;
	}
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

oepControlPoint::oepControlPoint(const osg::AnimationPath::ControlPoint& cp) : _handle(new osg::AnimationPath::ControlPoint()), _ownhandle(true)
{
	(*_handle) = cp;
}

double oepControlPoint::Time::get()
{
	return _time;
}

void oepControlPoint::Time::set(double v)
{
	_time = v;
}
