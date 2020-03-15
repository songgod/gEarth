#pragma once

namespace gEarthPack
{
	class MouseEventHandler : public osgGA::GUIEventHandler
	{
	public:
		struct MouseCallback : public osg::Referenced
		{
			virtual void onMouseDown(MouseEventHandler* sender, const osg::Vec3d& coords, int keybutton) = 0;
			virtual void onMouseUp(MouseEventHandler* sender, const osg::Vec3d& coords, int keybutton) = 0;
			virtual void onMouseMove(MouseEventHandler* sender, const osg::Vec3d& coords, int keybutton) = 0;
			virtual void onMouseDrag(MouseEventHandler* sender, const osg::Vec3d& coords, int keybutton) = 0;
			virtual void onMouseDoubleClick(MouseEventHandler* sender, const osg::Vec3d& coords, int keybutton) = 0;

			virtual ~MouseCallback() { }
		};

	public:
		MouseEventHandler();
		virtual ~MouseEventHandler();

	public:

		void setMapNode(osgEarth::MapNode* pMapNode) { _mapNode = pMapNode; }

		typedef std::vector< osg::ref_ptr<MouseCallback> > MouseCallbacks;
		MouseCallbacks& getMouseCallbacks() { return _callbacks; }
		const MouseCallbacks& getMouseCallbacks() const { return _callbacks; }

	public:

		virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	protected:

		bool getGeoPoint(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa, osg::Vec3d& point);

	protected:
		
		MouseCallbacks _callbacks;
		osgEarth::MapNode*      _mapNode;
	};
}


