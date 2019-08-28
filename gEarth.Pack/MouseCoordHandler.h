#pragma once

namespace gEarthPack
{
	class MouseCoordHandler : public osgGA::GUIEventHandler
	{
	public:
		struct MouseMoveCallback : public osg::Referenced
		{
			virtual void update(MouseCoordHandler* sender, const osg::Vec3& coords) = 0;

			virtual ~MouseMoveCallback() { }
		};

	public:
		MouseCoordHandler();
		virtual ~MouseCoordHandler();

	public:

		void setMapNode(osgEarth::MapNode* pMapNode) { _mapNode = pMapNode; }

		void addMoveCallback(MouseMoveCallback* callback);

	public:

		virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	protected:
		typedef std::vector< osg::ref_ptr<MouseMoveCallback> > MoveCallbacks;
		MoveCallbacks _callbacks;
		osgEarth::MapNode*      _mapNode;
	};
}


