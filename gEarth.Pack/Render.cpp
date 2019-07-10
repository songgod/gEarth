// This is the main DLL file.

#include "stdafx.h"

#include "Render.h"

#include <string>  
#include <msclr\marshal_cppstd.h>  

using namespace msclr::interop;

gEarthPack::Render::Render():_viewer(NULL)
{

}

void gEarthPack::Render::Start(IntPtr hwnd)
{
	if (_viewer)
		return;

	HWND h = (HWND)hwnd.ToPointer();
	_viewer = new Viewer(h);
	_viewer->init();
	_viewer->start();
}

void gEarthPack::Render::End()
{
	if (_viewer)
	{
		delete _viewer;
		_viewer = NULL;
	}
}

bool gEarthPack::Render::Open(oepMap^ map)
{
	osgEarth::MapNode* pMapNode = map->getMapNode();
	if (!pMapNode)
		return false;

	_viewer->open(pMapNode);
	return true;
}

void gEarthPack::Render::Flyto(oepViewpoint^ vp)
{
	if (vp == nullptr || vp->asoeViewpoint() == NULL)
		return;
	_viewer->flyto(*(vp->asoeViewpoint()));
}

gEarthPack::oepViewpoint^ gEarthPack::Render::GetViewpoint()
{
	osgEarth::Viewpoint vp = _viewer->getViewpoint();
	return gcnew gEarthPack::oepViewpoint(vp);
}
