#pragma once
#include "oepValObject.h"
#include "oepBounds.h"

namespace gEarthPack
{
	public ref class oepQuery :
		public oepValObject<osgEarth::Symbology::Query>
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

	private:

		oepBounds^ _bounds;
	};
}


