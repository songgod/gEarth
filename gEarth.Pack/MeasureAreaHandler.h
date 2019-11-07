#pragma once
#include "MeasureBaseHandler.h"

namespace gEarthPack
{
	class MeasureAreaHandler : public MeasureBaseHandler
	{
	public:
		MeasureAreaHandler(osgEarth::MapNode* pMapNode);
		~MeasureAreaHandler();

	public:

		class MeasureAreaResultHandler : public osg::Referenced
		{
		public:
			virtual void onAreaChanged(MeasureAreaHandler* sender, double area) = 0;
		};

	public:

		typedef std::vector<osg::ref_ptr<MeasureAreaResultHandler>> ResultHandlers;
		ResultHandlers& getResHandlers() { return _reshandlers; }
		const ResultHandlers& getResHandlers() const { return _reshandlers; }

	public:

		virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);
		virtual osgEarth::Features::Feature* createFeature();
		virtual void fireMeasureChanged();
		virtual void clear();

	private:

		bool _lastPointTemporary;
		bool _gotFirstLocation;
		bool _finished;
		bool _mouseDown;
		float _mouseDownX, _mouseDownY;
		ResultHandlers _reshandlers;
	};
}


