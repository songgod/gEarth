#pragma once
#include "MeasureBaseHandler.h"
namespace gEarthPack
{
	class MeasureVisibilityLineHandler : public MeasureBaseHandler
	{
	public:
		MeasureVisibilityLineHandler();
		~MeasureVisibilityLineHandler();

	public:

		virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
		virtual void rebuild();
		virtual void clear();

	protected:

		osg::ref_ptr<osgEarth::Util::LinearLineOfSightNode> _lineofsightnode;
		bool _startValid;
	};
}

