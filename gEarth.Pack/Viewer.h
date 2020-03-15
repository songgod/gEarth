#pragma once

#include "PlayPathHandler.h"

namespace gEarthPack
{
	class Viewer
	{
	public:

		Viewer(HWND hWnd);
		~Viewer();

	public:

		void init();

		void open(osgEarth::MapNode* mapnode);

		void clear();

		void start();

		void pause();

		void resume();

		osgViewer::Viewer* getViewer() const { return _viewer; }

		osg::Group* getRoot() const { return _root; }

		osgEarth::MapNode* getMapNode() const { return _mapnode; }

		void setClearColor(const osg::Vec4& color);

		const osg::Vec4& getClearColor() const;

		void flyto(const osgEarth::Viewpoint& vp);

		osgEarth::Viewpoint getViewpoint();

		void playPath(osg::AnimationPath* path);

	protected:

		void InitCameraConfig();
		void frame();

	private:

		HWND _hWnd;
		osgViewer::Viewer* _viewer;
		osgEarth::MapNode* _mapnode;
		osg::Group* _root;
		PlayPathHandler* _playpathmp;
		void* _renderthread;
	};
}