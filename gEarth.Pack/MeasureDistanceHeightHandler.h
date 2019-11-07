#pragma once
#include "MeasureBaseHandler.h"

namespace gEarthPack
{
	class MeasureDistanceHeightHandler : public MeasureBaseHandler
	{
	public:

		class MeasureToolEventHandler : public osg::Referenced
		{
		public:
			virtual void onDistanceHeightChanged(MeasureDistanceHeightHandler* sender, double distance, double height) {}
			virtual ~MeasureToolEventHandler() { }
		};

		typedef std::list< osg::ref_ptr< MeasureToolEventHandler > > MeasureToolEventHandlerList;

	public:

		MeasureDistanceHeightHandler(osgEarth::MapNode* mapNode);
		virtual ~MeasureDistanceHeightHandler();

	public:

		void addEventHandler(MeasureToolEventHandler* handler);

		void setIsPath(bool path);
		bool getIsPath() const;

	public:

		virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
		virtual void clear();
		virtual void fireMeasureChanged();
		virtual osgEarth::Features::Feature* createFeature();

	protected:
		
		bool _lastPointTemporary;
		bool _gotFirstLocation;
		bool _finished;
		bool _mouseDown;
		float _mouseDownX, _mouseDownY;
		bool _isPath;

		MeasureToolEventHandlerList _eventHandlers;
		
	};
}

