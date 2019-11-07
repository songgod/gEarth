#pragma once
namespace gEarthPack
{
	class MeasureBaseHandler : public osgGA::GUIEventHandler, public osgEarth::MapNodeObserver
	{
	public:
		MeasureBaseHandler(osgEarth::MapNode* mapNode);
		virtual ~MeasureBaseHandler();

	public:

		osgEarth::GeoInterpolation getGeoInterpolation() const;
		void setGeoInterpolation(osgEarth::GeoInterpolation geoInterpolation);

		void setIntersectionMask(osg::Node::NodeMask intersectionMask) { _intersectionMask = intersectionMask; }
		osg::Node::NodeMask getIntersectionMask() const { return _intersectionMask; }

	public:

		virtual void setMapNode(osgEarth::MapNode* mapNode);
		virtual osgEarth::MapNode* getMapNode() { return _mapNode.get(); }
		virtual void fireMeasureChanged(){}
		virtual void rebuild();
		virtual osgEarth::Features::Feature* createFeature() { return 0L;}
		virtual void clear();

	protected:

		bool getLocationAt(osgViewer::View* view, double x, double y, osg::Vec3d& p, osg::Vec3d& n);
		osg::Vec3d xyz2latlnghigh(const osg::Vec3d& xyz);
		osg::Vec3d latlnghigh2xyz(const osg::Vec3d& llh);

	protected:

		osg::observer_ptr< osgEarth::MapNode > _mapNode;
		osg::ref_ptr< osg::Group > _root;
		osg::ref_ptr< osgEarth::Annotation::FeatureNode > _featureNode;
		osg::ref_ptr< osgEarth::Features::Feature >  _feature;
		osgEarth::GeoInterpolation _geoInterpolation;
		osg::Node::NodeMask _intersectionMask;
		int _mouseButton;
	};
}

