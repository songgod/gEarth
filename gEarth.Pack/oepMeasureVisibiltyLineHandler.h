#pragma once
#include "oepEventHandler.h"
namespace gEarthPack
{
	public ref class oepMeasureVisibiltyLineHandler :
		public oepEventHandler
	{
	public:
		oepMeasureVisibiltyLineHandler();

	internal:
		virtual void bind(osgEarth::MapNode* pMapNode) override;
		virtual void unbind(osgEarth::MapNode* pMapNode) override;

	protected:

		unsigned int _nodemask;
	};
}
