#pragma once

#include <vector>

namespace gEarthPack
{
	class CalcMath
	{
	public:
		CalcMath();
		~CalcMath();

	public:

		static double calcArea(const std::vector<osg::Vec3d>& points, osgEarth::MapNode* mapnode);
		static double calcSurfaceArea(const std::vector<osg::Vec3d>& points, osgEarth::MapNode* mapnode);
		static double calcRhumbArea(const std::vector<osg::Vec3d>& points, osgEarth::MapNode* mapnode);
		static double calcRhumbSurfaceArea(const std::vector<osg::Vec3d>& points, osgEarth::MapNode* mapnode);
	};
}


