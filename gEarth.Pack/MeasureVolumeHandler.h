#pragma once
#include "MeasureBaseHandler.h"

namespace gEarthPack
{
	class MeasureVolumeHandler : public MeasureBaseHandler
	{
	public:
		MeasureVolumeHandler(osgEarth::MapNode* mapNode);
		~MeasureVolumeHandler();
	};
}


