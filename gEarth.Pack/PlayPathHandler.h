#pragma once

#include <osgGA/GUIEventHandler>
#include <osg/AnimationPath>
#include <osgGA/AnimationPathManipulator>

namespace gEarthPack
{
	class PlayPathHandler : public osgGA::GUIEventHandler
	{
	public:
		PlayPathHandler();

	public:

		void playPath(osg::AnimationPath* path);

	public:

		virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);

	protected:

		osg::ref_ptr<osg::AnimationPath> _animationpath;
		osg::ref_ptr<osgGA::AnimationPathManipulator> _animPathManipulator;
		osg::ref_ptr<osgGA::CameraManipulator> _oldCameraManipulator;
		bool _currentplaying;
	};
}

