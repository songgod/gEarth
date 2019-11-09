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

		void setSurface(bool b);
		bool getSurface() const { return _bsurface; }

	public:

		virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);
		virtual osgEarth::Features::Feature* createFeature();
		virtual void fireMeasureChanged();
		virtual void clear();

	private:

		bool _bsurface;
		bool _bnewmeasure;
		ResultHandlers _reshandlers;
	};
}


