#pragma once
#include "oepEventHandler.h"
#include "oepRender.h"
#include "oepVector.h"

namespace gEarthPack
{
	ref class oepMouseEventHandler;
	public delegate void MouseDownEvent(oepMouseEventHandler^ handle, oepVec3f p, int keybutton);
	public delegate void MouseUpEvent(oepMouseEventHandler^ handle, oepVec3f p, int keybutton);
	public delegate void MouseMoveEvent(oepMouseEventHandler^ handle, oepVec3f p, int keybutton);
	public delegate void MouseDragEvent(oepMouseEventHandler^ handle, oepVec3f p, int keybutton);
	public delegate void MouseDoubleClickEvent(oepMouseEventHandler^ handle, oepVec3f p, int keybutton);

	public ref class oepMouseEventHandler :
		public oepEventHandler
	{
	public:
		oepMouseEventHandler();

	public:

		event MouseDownEvent^ OnMouseDown;
		event MouseUpEvent^ OnMouseUp;
		event MouseMoveEvent^ OnMouseMove;
		event MouseDragEvent^ OnMouseDrag;
		event MouseDoubleClickEvent^ OnMouseDoubleClick;

	public:

		void FireMouseDown(oepVec3f p, int keybutton);
		void FireMouseUp(oepVec3f p, int keybutton);
		void FireMouseMove(oepVec3f p, int keybutton);
		void FireMouseDrag(oepVec3f p, int keybutton);
		void FireMouseDoubleClick(oepVec3f p, int keybutton);

	internal:
		virtual void bind(osgEarth::MapNode* pMapNode) override;
		virtual void unbind(osgEarth::MapNode* pMapNode) override;
	};
}

