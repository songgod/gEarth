#include "stdafx.h"

#include "PlayPathHandler.h"

using namespace gEarthPack;

PlayPathHandler::PlayPathHandler():_currentplaying(false)
{
}

void PlayPathHandler::playPath(osg::AnimationPath* path)
{
	_animationpath = path;
}

bool PlayPathHandler::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
	if (view == NULL)
		return false;

	if (_animationpath.valid() && !_animationpath->empty() && !_currentplaying)
	{
		_animPathManipulator = new osgGA::AnimationPathManipulator(_animationpath.get());
		_animPathManipulator->home(ea, aa);
		_oldCameraManipulator = view->getCameraManipulator();
		view->setCameraManipulator(_animPathManipulator.get());
		_currentplaying = true;
		return false;
	}

	if (ea.getEventType() == osgGA::GUIEventAdapter::PUSH)
	{
		if (_oldCameraManipulator.valid())
		{
			view->setCameraManipulator(_oldCameraManipulator.get(),false);
			if (_animPathManipulator.valid())
				_oldCameraManipulator->setByMatrix(_animPathManipulator->getMatrix());
		}
		_currentplaying = false;
		_animationpath = NULL;
		_animPathManipulator = NULL;
		_oldCameraManipulator = NULL;
	}

	return false;
}
