// This is the main DLL file.

#include "stdafx.h"

#include "Render.h"

#include <string>  
#include <msclr\marshal_cppstd.h>  

using namespace msclr::interop;

gEarthPack::Render::Render():_viewer(NULL)
{

}

gEarthPack::Render::!Render()
{
	End();
}

gEarthPack::Render::~Render()
{
	End();
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

bool gEarthPack::Render::Open(String^ url)
{
	if (!_viewer)
		return false;
	return _viewer->open(marshal_as<std::string>(url));
}
