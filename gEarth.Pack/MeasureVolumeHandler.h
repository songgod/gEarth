#pragma once
#include "MeasureBaseHandler.h"

namespace gEarthPack
{
	class MeasureVolumeHandler : public MeasureBaseHandler
	{
	public:
		MeasureVolumeHandler();
		~MeasureVolumeHandler();

	public:

		class MeasureVolumeResultHandler : public osg::Referenced
		{
		public:
			virtual void onVolumeChanged(MeasureVolumeHandler* sender, double volume) = 0;
		};

	public:

		typedef std::vector<osg::ref_ptr<MeasureVolumeResultHandler>> ResultHandlers;
		ResultHandlers& getResHandlers() { return _reshandlers; }
		const ResultHandlers& getResHandlers() const { return _reshandlers; }

		void setDeep(double d);
		double getDeep() const;

	public:

		virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);
		virtual osgEarth::Features::Feature* createFeature();
		virtual void fireMeasureChanged();
		virtual void clear();

	private:

		bool _bnewmeasure;
		ResultHandlers _reshandlers;
		double _deep;
	};
}


