#pragma once
#include "oepValObject.h"
#include "oepValList.h"
namespace gEarthPack
{
	public ref class oepStyleSelector :
		public oepValObject<osgEarth::Symbology::StyleSelector>
	{
	public:
		oepStyleSelector();
	};

	public ref class oepStyleSelectorList : public oepValList<oepStyleSelector, osgEarth::Symbology::StyleSelector>
	{
		
	};
}

