#pragma once

#include <osgViewer/Viewer>
#include <osg/Group>
#include <osgEarth/MapNode>
#include <windows.h>
#include <osgEarth/Viewpoint>

/** ��Ⱦ����*/
class Viewer
{
public:

	Viewer(HWND hWnd);
	~Viewer();

public:

	/** ��ʼ��*/
	void init();

	/** �򿪽ڵ�*/
	void open(osgEarth::MapNode* mapnode);

	/** ��սڵ�*/
	void clear();

	/** ��ʼ��Ⱦ*/
	void start();

	/** ��ͣ��Ⱦ������ͣ��Ⱦ����ԶԳ��������޸�*/
	void pause();

	/** �ָ���Ⱦ*/
	void resume();

	/** ��ȡosg�Ӵ�*/
	osgViewer::Viewer* getViewer() const { return _viewer; }

	/** ��ȡ���ڵ�*/
	osg::Group* getRoot() const { return _root; }

	/** ��ȡMapNode*/
	osgEarth::MapNode* getMapNode() const { return _mapnode; }

	/** ���ñ���ɫ*/
	void setClearColor(const osg::Vec4& color);

	/** ��ȡ����ɫ*/
	const osg::Vec4& getClearColor() const;

	/**���е��ӵ�*/
	void flyto(const osgEarth::Viewpoint& vp);

protected:

	void InitCameraConfig();
	void frame();

private:

	HWND _hWnd;
	osgViewer::Viewer* _viewer;
	osgEarth::MapNode* _mapnode;
	osg::Group* _root;
	void* _renderthread;
};