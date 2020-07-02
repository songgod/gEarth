#pragma once
#include "oepValObject.h"
namespace gEarthPack
{
	public ref class oepFeatureSourceIndexOptions :
		public oepValObject
	{
	public:
		oepFeatureSourceIndexOptions();

	internal:

		virtual void delelehandle() override;
	};
}

