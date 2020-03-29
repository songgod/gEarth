#pragma once
#include "oepSymbol.h"
#include "oepFill.h"

namespace gEarthPack
{
	public ref class oepPolygonSymbol :
		public oepSymbol
	{
	public:
		oepPolygonSymbol();

	public:

		property oepFill^ Fill
		{
			oepFill^ get();
			void set(oepFill^ p);
		}

		property bool OutLine
		{
			bool get();
			void set(bool p);
		}

	internal:

		virtual void binded() override;
		virtual void unbinded() override;

	protected:

		oepFill^ _fill;
	};
}
