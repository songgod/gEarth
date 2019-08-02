#pragma once

#include <osgGA/GUIEventHandler>
#include <osgEarthAnnotation/FeatureNode>
#include <osgEarthSymbology/Style>
#include <osgEarth/GeoCommon>
#include <osgViewer/View>

namespace osgEarth
{
	class MapNode;
}
namespace gEarthPack
{
	class MeasureAreaHandler : public osgGA::GUIEventHandler, public osgEarth::MapNodeObserver
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

		void setIntersectionMask(osg::Node::NodeMask intersectionMask) { _intersectionMask = intersectionMask; }
		osg::Node::NodeMask getIntersectionMask() const { return _intersectionMask; }

		osgEarth::GeoInterpolation getGeoInterpolation() const;
		void setGeoInterpolation(osgEarth::GeoInterpolation geoInterpolation);

		void setMouseButton(int mouseButton);
		int getMouseButton() const;

	public:

		virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);

	public: // MapNodeObserver

		virtual void setMapNode(osgEarth::MapNode* mapNode);
		virtual osgEarth::MapNode* getMapNode() { return _mapnode.get(); }

	protected:

		void rebuild();
		void fireAreaChanged();
		bool getLocationAt(osgViewer::View* view, double x, double y, double &lon, double &lat);
		void clear();

	private:

		bool _lastPointTemporary;
		bool _gotFirstLocation;
		bool _finished;
		bool _mouseDown;
		float _mouseDownX, _mouseDownY;
		int _mouseButton;
		ResultHandlers _reshandlers;
		osg::observer_ptr<osgEarth::MapNode> _mapnode;
		osg::Node::NodeMask _intersectionMask;
		osg::ref_ptr< osgEarth::Annotation::FeatureNode > _featureNode;
		osg::ref_ptr< osgEarth::Features::Feature >  _feature;
		osg::ref_ptr< osg::Group > _root;
		osgEarth::GeoInterpolation _geointerpolation;
	};
}


