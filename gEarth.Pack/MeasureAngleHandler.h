#pragma once
namespace gEarthPack
{
	class MeasureAngleHandler : public osgGA::GUIEventHandler, public osgEarth::MapNodeObserver
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

		osgEarth::GeoInterpolation getGeoInterpolation() const;
		void setGeoInterpolation(osgEarth::GeoInterpolation geoInterpolation);

		void setIntersectionMask(osg::Node::NodeMask intersectionMask) { _intersectionMask = intersectionMask; }
		osg::Node::NodeMask getIntersectionMask() const { return _intersectionMask; }

	public:

		virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
		virtual void setMapNode(osgEarth::MapNode* mapNode);
		virtual osgEarth::MapNode* getMapNode() { return _mapNode.get(); }

	protected:

		bool getLocationAt(osgViewer::View* view, double x, double y, double &lon, double &lat, double &height);
		void fireAngleChanged();
		void rebuild();
		void clear();

	protected:

		MeasureAngleEventHandlerList _eventHandlers;
		osg::observer_ptr< osgEarth::MapNode > _mapNode;
		osg::ref_ptr< osg::Group > _root;
		osg::ref_ptr< osgEarth::Annotation::FeatureNode > _featureNode;
		osg::ref_ptr< osgEarth::Features::Feature >  _feature;
		osgEarth::GeoInterpolation _geoInterpolation;
		osg::Node::NodeMask _intersectionMask;
		int _mouseButton;
		bool _bNewMesura;
	};
}

