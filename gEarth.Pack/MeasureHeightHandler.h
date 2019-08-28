#pragma once

namespace gEarthPack
{
	class MeasureHeightHandler : public osgGA::GUIEventHandler, public osgEarth::MapNodeObserver
	{
	public:
		MeasureHeightHandler(osgEarth::MapNode* pMapNode);
		~MeasureHeightHandler();

	public:

		class MeasureHeightResultHandler : public osg::Referenced
		{
		public:
			virtual void onAreaChanged(MeasureHeightHandler* sender, double area) = 0;
		};

	public:

		typedef std::vector<osg::ref_ptr<MeasureHeightResultHandler>> ResultHandlers;
		ResultHandlers& getResHandlers() { return _reshandlers; }
		const ResultHandlers& getResHandlers() const { return _reshandlers; }

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

		ResultHandlers _reshandlers;
		osg::observer_ptr<osgEarth::MapNode> _mapnode;
		osg::Node::NodeMask _intersectionMask;
		osg::ref_ptr< osgEarth::Annotation::FeatureNode > _featureNode;
		osg::ref_ptr< osgEarth::Features::Feature >  _feature;
		osg::ref_ptr< osg::Group > _root;
	};
}

