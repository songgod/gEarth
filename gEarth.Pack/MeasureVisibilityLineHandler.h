#pragma once
#include "MeasureBaseHandler.h"
namespace gEarthPack
{
	class MeasureVisibilityLineHandler : public MeasureBaseHandler
	{
	public:
		MeasureVisibilityLineHandler(osgEarth::MapNode* mapNode);
		~MeasureVisibilityLineHandler();

	public:

		virtual void rebuild();
		virtual void clear();

	protected:

		osg::ref_ptr<osgEarth::Util::LinearLineOfSightNode> _lineofsightnode;
	};
}

