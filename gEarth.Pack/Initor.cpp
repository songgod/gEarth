#include "Stdafx.h"
#include <direct.h>
#include <string>

namespace gEarthPack
{
	class Initor
	{
	public:
		Initor()
		{
			char c[1024];
			_getcwd(c, 1024);

			std::string pathgdal = "GDAL_DATA=" + std::string(c) + "\\gdal_data";
			_putenv(pathgdal.c_str());
		}
	};

	static Initor s_initor;
}