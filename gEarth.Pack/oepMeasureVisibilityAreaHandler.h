#pragma once
#include "oepEventHandler.h"
namespace gEarthPack
{
	public ref class oepMeasureVisibilityAreaHandler :
		public oepEventHandler
	{
	public:
		oepMeasureVisibilityAreaHandler();

	internal:
		virtual void bind(osgEarth::MapNode* pMapNode) override;
		virtual void unbind(osgEarth::MapNode* pMapNode) override;

	protected:

		unsigned int _nodemask;
	};
}

