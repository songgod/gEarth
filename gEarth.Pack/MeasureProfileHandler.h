#pragma once
#include "MeasureBaseHandler.h"

namespace gEarthPack
{
	class MeasureProfileHandler : public MeasureBaseHandler
	{		
	public:
		MeasureProfileHandler();
		~MeasureProfileHandler();

	public:

		osgEarth::Util::TerrainProfileCalculator* getProfileCalculator() { return _profileCalculator.get(); }
		const osgEarth::Util::TerrainProfileCalculator* getProfileCalculator() const { return _profileCalculator.get(); }

	public:

		virtual void setMapNode(osgEarth::MapNode* mapNode);
		virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
		virtual osgEarth::Features::Feature* createFeature();
		virtual void fireMeasureChanged();
		virtual void clear();

	protected:

		osg::ref_ptr<osgEarth::Util::TerrainProfileCalculator> _profileCalculator;
		bool _startValid;
	};
}

