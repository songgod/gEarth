#pragma once
#include "oepExtension.h"
#include "oepVector.h"

using namespace System::Collections::Generic;

namespace gEarthPack
{
	public ref class oepContourMapExtension :
		public oepExtension
	{
	public:
		oepContourMapExtension();

	public:

		property Dictionary<float, oepVec4f>^ ColorMap
		{
			void set(Dictionary<float, oepVec4f>^ cm);
			Dictionary<float, oepVec4f>^ get();
		}

	internal:
		oepContourMapExtension(osgEarth::Extension* ext);
		osgEarth::Util::ContourMap* getoeContourMap();

	private:

		bool _bVisible;
	};
}

