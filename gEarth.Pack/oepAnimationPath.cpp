#include "stdafx.h"
#include "oepAnimationPath.h"
#include <msclr\marshal_cppstd.h>  

using namespace msclr::interop;

gEarthPack::oepAnimationPath::oepAnimationPath()
{
	_handle = new AnimationPathInfoHandle(new AnimationPathInfo());
	_controlpoints = gcnew oepControlPoints();
	init();
	_controlpoints->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &gEarthPack::oepAnimationPath::OnControlPointsCollectionChanged);
}

gEarthPack::oepAnimationPath::!oepAnimationPath()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

gEarthPack::oepAnimationPath::~oepAnimationPath()
{
	if (_handle != NULL)
	{
		delete _handle;
		_handle = NULL;
	}
}

void gEarthPack::oepAnimationPath::PlayPath(oepAnimationPath^ path, Render^ render)
{
	if (render==nullptr || render->_viewer==NULL ||
		path== nullptr || path->asoeAnimationPathInfo() == NULL || path->asoeAnimationPathInfo()->animationpath() == NULL)
		return;
	render->_viewer->playPath(path->asoeAnimationPathInfo()->animationpath());
}

gEarthPack::oepAnimationPath^ gEarthPack::oepAnimationPath::From(String^ url)
{
	if (String::IsNullOrEmpty(url))
		return nullptr;
	AnimationPathInfo* info = new AnimationPathInfo();
	info->name() = marshal_as<std::string>(System::IO::Path::GetFileNameWithoutExtension(url));
	info->url() = marshal_as<std::string>(url);
	
	oepAnimationPath^ res = gcnew oepAnimationPath(info);
	return res;
}

bool gEarthPack::oepAnimationPath::Save()
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

gEarthPack::oepAnimationPath::oepAnimationPath(AnimationPathInfo* info)
{
	_handle = new AnimationPathInfoHandle(info);
	_controlpoints = gcnew oepControlPoints();
	init();
	_controlpoints->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &gEarthPack::oepAnimationPath::OnControlPointsCollectionChanged);
}

osgEarth::AnimationPath::AnimationPathInfo* gEarthPack::oepAnimationPath::asoeAnimationPathInfo()
{
	return _handle != NULL ? _handle->getValue() : NULL;
}

void gEarthPack::oepAnimationPath::init()
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

void gEarthPack::oepAnimationPath::OnControlPointsCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e)
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

String^ gEarthPack::oepAnimationPath::Name::get()
{
	AnimationPathInfo *ap = asoeAnimationPathInfo();
	if (!ap)
		return "";
	return marshal_as<String^>(ap->name());
}

void gEarthPack::oepAnimationPath::Name::set(String^ v)
{
	AnimationPathInfo *ap = asoeAnimationPathInfo();
	if (!ap)
		return;

	ap->name() = marshal_as<std::string>(v);
	NotifyChanged("Name");
}

String^ gEarthPack::oepAnimationPath::Url::get()
{
	AnimationPathInfo *ap = asoeAnimationPathInfo();
	if (!ap)
		return "";
	return marshal_as<String^>(ap->url());
}

void gEarthPack::oepAnimationPath::Url::set(String^ v)
{
	AnimationPathInfo *ap = asoeAnimationPathInfo();
	if (!ap)
		return;

	ap->url() = marshal_as<std::string>(v);
	NotifyChanged("Url");
}

gEarthPack::oepControlPoints^ gEarthPack::oepAnimationPath::ControlPoints::get()
{
	return _controlpoints;
}

gEarthPack::oepControlPoint::oepControlPoint() : _handle(new osg::AnimationPath::ControlPoint()), _ownhandle(true),_time(0.0)
{

}

void gEarthPack::oepControlPoint::setHandle(osg::AnimationPath::ControlPoint* cp)
{
	if (_handle != NULL && _ownhandle)
	{
		delete _handle;
		_handle = NULL;
	}
	_handle = cp;
	_ownhandle = false;
}

void gEarthPack::oepControlPoint::resetHandle()
{
	if (_ownhandle)
		return;
	_handle = new osg::AnimationPath::ControlPoint();
	_ownhandle = true;
}

osg::AnimationPath::ControlPoint* gEarthPack::oepControlPoint::asosgControlPoint()
{
	return _handle;
}

gEarthPack::oepControlPoint::~oepControlPoint()
{
	if (_handle != NULL && _ownhandle)
	{
		delete _handle;
		_handle = NULL;
	}
}

gEarthPack::oepControlPoint::!oepControlPoint()
{
	if (_handle != NULL && _ownhandle)
	{
		delete _handle;
		_handle = NULL;
	}
}

gEarthPack::oepControlPoint^ gEarthPack::oepControlPoint::MakeControlPoint(Render^ render, double time)
{
	if (render == nullptr || render->_viewer==NULL || render->_viewer->getViewer()==NULL)
		return nullptr;
	const osg::Matrixd& m = render->_viewer->getViewer()->getCamera()->getInverseViewMatrix();
	osg::AnimationPath::ControlPoint cp(m.getTrans(), m.getRotate());
	gEarthPack::oepControlPoint^ oepcp = gcnew gEarthPack::oepControlPoint(cp);
	oepcp->Time = time;
	return oepcp;
}

gEarthPack::oepControlPoint::oepControlPoint(const osg::AnimationPath::ControlPoint& cp) : _handle(new osg::AnimationPath::ControlPoint()), _ownhandle(true)
{
	(*_handle) = cp;
}

double gEarthPack::oepControlPoint::Time::get()
{
	return _time;
}

void gEarthPack::oepControlPoint::Time::set(double v)
{
	_time = v;
}
