#pragma once
#include "MeasureBaseHandler.h"
namespace gEarthPack
{
	class MeasureAngleHandler : public MeasureBaseHandler
	{
	public:

		class MeasureAngleEventHandler : public osg::Referenced
		{
		public:
			virtual void onAngleChanged(MeasureAngleHandler* sender, double angle) {}
			virtual ~MeasureAngleEventHandler() { }
		};

		typedef std::list< osg::ref_ptr< MeasureAngleEventHandler > > MeasureAngleEventHandlerList;

	public:
		MeasureAngleHandler(osgEarth::MapNode* mapNode);
		virtual ~MeasureAngleHandler();

	public:

		void addEventHandler(MeasureAngleEventHandler* handler);

	public:

		virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
		virtual osgEarth::Features::Feature* createFeature();
		virtual void fireMeasureChanged();
		virtual void clear();

	protected:

		MeasureAngleEventHandlerList _eventHandlers;
		bool _bNewMesura;
	};
}

