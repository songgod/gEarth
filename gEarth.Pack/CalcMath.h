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
		static double calcVolume(const std::vector<osg::Vec3d>& points, osgEarth::MapNode* mapnode, double deep);
		static double calcRhumbArea(const std::vector<osg::Vec3d>& points, osgEarth::MapNode* mapnode, unsigned int numparts=100);
		static double calcRhumbSurfaceArea(const std::vector<osg::Vec3d>& points, osgEarth::MapNode* mapnode, unsigned int numparts=100);
		static double calcRhumbVolume(const std::vector<osg::Vec3d>& points, osgEarth::MapNode* mapnode, double deep, unsigned int numparts = 100);
		static double caltrianglearea(const osg::Vec3d& a, const osg::Vec3d& b, const osg::Vec3d& c);

		static void trianglation(const std::vector<osg::Vec3d>& points, std::vector<std::vector<osg::Vec3d>>& triangles, double minarea);

		static osg::Vec3d latlnghigh2xyz(osgEarth::MapNode* mapnode, const osg::Vec3d& llh);
		static osg::Vec3d xyz2latlnghigh(osgEarth::MapNode* mapnode, const osg::Vec3d& xyz);
	};
}


