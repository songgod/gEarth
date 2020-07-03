#pragma once
#include "oepValObject.h"
#include "oepVector.h"

namespace gEarthPack
{
	public ref class oepFill :
		public oepValObject
	{
	public:
		oepFill();

	public:

		property oepVec4f Color
		{
			oepVec4f get();
			void set(oepVec4f p);
		}

	internal:

		virtual void delelehandle() override;
	};
}

