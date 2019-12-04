#pragma once
#include "oepRefObject.h"
#include "oepValMap.h"
using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	public ref class oepResourceLibrary :
		public oepRefObject<osgEarth::Symbology::ResourceLibrary>
	{
	public:
		oepResourceLibrary();
	};

	public ref class oepResourceLibraryMap : public ObservableCollection<oepResourceLibrary^>
	{

	};
}

