#pragma once
#include "oepValObject.h"
namespace gEarthPack
{
	public ref class oepFeatureDisplayLayout :
		public oepValObject
	{
	public:
		oepFeatureDisplayLayout();

	internal:

		virtual void delelehandle() override;
	};
}

