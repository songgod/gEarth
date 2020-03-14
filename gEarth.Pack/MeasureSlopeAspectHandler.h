#pragma once
#include "MeasureBaseHandler.h"
namespace gEarthPack
{
	class MeasureSlopeAspectHandler : public MeasureBaseHandler
	{
	public:

		class MeasureSlopeAspectEventHandler : public osg::Referenced
		{
		public:
			virtual void onSlopeAspectChanged(MeasureSlopeAspectHandler* sender, double slope, double aspect, osg::Vec3 point) {}
			virtual ~MeasureSlopeAspectEventHandler() { }
		};

		typedef std::list< osg::ref_ptr< MeasureSlopeAspectEventHandler > > MeasureSlopeAspectEventHandlerList;

	public:
		MeasureSlopeAspectHandler();
		~MeasureSlopeAspectHandler();

	public:

		void addEventHandler(MeasureSlopeAspectEventHandler* handler);

	public:

		virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
		virtual osgEarth::Features::Feature* createFeature();
		virtual void fireMeasureChanged();
		virtual void clear();

	protected:

		bool calSlopeAspectDegree(const osg::Vec3d& p, const osg::Vec3d& n, double &slope, double &aspect);

	protected:

		MeasureSlopeAspectEventHandlerList _eventHandlers;
		double _slope;
		double _aspect;
		osg::Vec3 _point;
	};
}
