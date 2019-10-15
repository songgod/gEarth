#pragma once

namespace gEarthPack
{
	class MeasureDistanceHeightHandler : public osgGA::GUIEventHandler, public osgEarth::MapNodeObserver
	{
	public:

		class MeasureToolEventHandler : public osg::Referenced
		{
		public:
			virtual void onDistanceHeightChanged(MeasureDistanceHeightHandler* sender, double distance, double height) {}
			virtual ~MeasureToolEventHandler() { }
		};

		typedef std::list< osg::ref_ptr< MeasureToolEventHandler > > MeasureToolEventHandlerList;


		MeasureDistanceHeightHandler(osgEarth::MapNode* mapNode);
		virtual ~MeasureDistanceHeightHandler();

		bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

		bool getLocationAt(osgViewer::View* view, double x, double y, double &lon, double &lat, double &height);

		void clear();

		void addEventHandler(MeasureToolEventHandler* handler);

		void setMouseButton(int mouseButton);
		int getMouseButton() const;

		osgEarth::GeoInterpolation getGeoInterpolation() const;
		void setGeoInterpolation(osgEarth::GeoInterpolation geoInterpolation);

		void setIsPath(bool path);
		bool getIsPath() const;

		/** Sets the style of the measurement line (to something other than the default) */
		void setLineStyle(const osgEarth::Symbology::Style& style);
		const osgEarth::Symbology::Style& getLineStyle() const { return _feature->style().value(); }

		void setIntersectionMask(osg::Node::NodeMask intersectionMask) { _intersectionMask = intersectionMask; }
		osg::Node::NodeMask getIntersectionMask() const { return _intersectionMask; }

		osgEarth::Features::Feature* getFeature() const { return _feature.get(); }

	public: // MapNodeObserver

		virtual void setMapNode(osgEarth::MapNode* mapNode);
		virtual osgEarth::MapNode* getMapNode() { return _mapNode.get(); }

	protected:
		osgEarth::GeoInterpolation _geoInterpolation;
		void fireDistanceChanged();
		bool _lastPointTemporary;
		bool _gotFirstLocation;
		bool _finished;
		bool _mouseDown;
		float _mouseDownX, _mouseDownY;
		int _mouseButton;
		osg::ref_ptr< osg::Group > _root;

		osg::ref_ptr< osgEarth::Annotation::FeatureNode > _featureNode;
		osg::ref_ptr< osgEarth::Features::Feature >  _feature;

		osg::ref_ptr< osgEarth::Annotation::FeatureNode > _extentFeatureNode;
		osg::ref_ptr< osgEarth::Features::Feature >       _extentFeature;

		MeasureToolEventHandlerList _eventHandlers;
		bool _isPath;
		osg::observer_ptr< osgEarth::MapNode > _mapNode;
		osg::Node::NodeMask _intersectionMask;

		void rebuild();
	};
}

