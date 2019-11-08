#pragma once
#include "MeasureBaseHandler.h"
namespace gEarthPack
{
	class MeasureVisibilityAreaHandler : public MeasureBaseHandler
	{
	public:
		MeasureVisibilityAreaHandler(osgEarth::MapNode* mapNode);
		~MeasureVisibilityAreaHandler();

	public:

		virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
		virtual void rebuild();
		virtual void clear();

	protected:

		osg::ref_ptr<osgEarth::Util::RadialLineOfSightNode> _radiaofsightnode;
		bool _startValid;
	};
}

