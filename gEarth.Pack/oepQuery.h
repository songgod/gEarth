#pragma once
#include "oepValObject.h"
#include "oepBounds.h"

using namespace osgEarth::Symbology;

namespace gEarthPack
{
	public ref class oepQuery :
		public oepValObject
	{
	public:
		oepQuery();

	public:

		property oepBounds^ Bounds
		{
			oepBounds^ get();
			void set(oepBounds^ p);
		}

		property String^ Expression
		{
			String^ get();
			void set(String^ p);
		}

		property String^ OrderBy
		{
			String^ get();
			void set(String^ p);
		}

		property int Limit
		{
			int get();
			void set(int p);
		}

	internal:

		virtual void binded() override;
		virtual void unbinded() override;
		virtual void delelehandle() override;

	private:

		oepBounds^ _bounds;
	};
}


