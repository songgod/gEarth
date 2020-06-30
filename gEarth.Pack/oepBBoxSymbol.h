#pragma once
#include "oepSymbol.h"
#include "oepFill.h"

namespace gEarthPack
{
	public ref class oepBBoxSymbol :
		public oepSymbol
	{
	public:
		oepBBoxSymbol();

	public:

		property oepFill^ Fill
		{
			oepFill^ get();
			void set(oepFill^ p);
		}



	protected:

		oepFill^ _fill;
	};
}

