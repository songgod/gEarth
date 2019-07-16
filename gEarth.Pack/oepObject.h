#pragma once

#include "oepNotify.h"

namespace gEarthPack
{
	public ref class oepObject : public oepNotify
	{
	public:
		oepObject();

	public:

		virtual property String^ Name
		{
			String^ get();
			void set(String^ v);
		}
	};
}


