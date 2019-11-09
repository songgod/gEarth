#include "stdafx.h"
#include "CalcMath.h"

using namespace gEarthPack;

namespace
{
	class TriangleResult
	{
	public:

		TriangleResult()
		{
			
		}

	public:

		void operator() (const osg::Vec3& v1, const osg::Vec3& v2, const osg::Vec3& v3, bool)
		{
			std::vector<osg::Vec3d> triangle;
			triangle.resize(3);
			triangle[0] = v1;
			triangle[1] = v2;
			triangle[2] = v3;
			_bigtriangles.push_back(triangle);
		}

	public:

		void createtriangles(std::vector<std::vector<osg::Vec3d>>& triangles, double minarea)
		{
			std::vector<std::vector<std::vector<osg::Vec3d>>> results;
			results.resize(_bigtriangles.size());
			double minarea2 = minarea*minarea;
#pragma omp parallel for
			for (size_t i = 0; i < _bigtriangles.size(); i++)
			{
				DecomposeTriangleArea(_bigtriangles[i][0], _bigtriangles[i][1], _bigtriangles[i][2], results[i], minarea);
			}

			for (size_t i = 0; i < results.size(); i++)
			{
				triangles.insert(triangles.end(), results[i].begin(), results[i].end());
			}
		}

	private:

		double getarea2(osg::Vec3d& v1, osg::Vec3d& v2, osg::Vec3d& v3) const
		{
			double a = (v1 - v2).length2();
			double b = (v1 - v3).length2();
			double c = (v3 - v2).length2();
			return ((c*a) - pow((c + a - b) / 2, 2)) / 4;
		}

		void DecomposeTriangleArea(osg::Vec3d& p1, osg::Vec3d& p2, osg::Vec3d& p3, std::vector<std::vector<osg::Vec3d>>& result, double minarea2)
		{

			double area2 = getarea2(p1, p2, p3);
			if (area2 < minarea2)
			{
				std::vector<osg::Vec3d> triangle;
				triangle.resize(3);
				triangle[0] = p1;
				triangle[1] = p2;
				triangle[2] = p3;
				result.push_back(triangle);
			}
			else
			{
				double d12 = (p1 - p2).length2();
				double d13 = (p1 - p3).length2();
				double d23 = (p3 - p2).length2();

				double maxd = max(d23, max(d12, d13));
				if (osg::equivalent(d12, maxd))
				{
					osg::Vec3d pc;
					pc = (p1 + p2) / 2.0;
					DecomposeTriangleArea(p1, pc, p3, result, minarea2);
					DecomposeTriangleArea(pc, p2, p3, result, minarea2);
				}
				else if (osg::equivalent(d13, maxd))
				{
					osg::Vec3d pc;
					pc = (p1 + p3) / 2.0;
					DecomposeTriangleArea(p2, pc, p1, result, minarea2);
					DecomposeTriangleArea(pc, p2, p3, result, minarea2);
				}
				else
				{
					osg::Vec3d pc;
					pc = (p2 + p3) / 2.0;
					DecomposeTriangleArea(p1, pc, p3, result, minarea2);
					DecomposeTriangleArea(pc, p1, p2, result, minarea2);
				}
			}
		}

	private:

		std::vector<std::vector<osg::Vec3d>> _bigtriangles;
	};
}

CalcMath::CalcMath()
{
}


CalcMath::~CalcMath()
{
}


void CalcMath::trianglation(const std::vector<osg::Vec3d>& points, std::vector<std::vector<osg::Vec3d>>& triangles, double minarea)
{
	if (minarea < 0)
		return;
	osg::ref_ptr<osg::Geometry> polyGeom = new osg::Geometry();
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	vertices->resize(points.size());
	for (size_t i = 0; i < points.size(); i++)
	{
		(*vertices)[i] = osg::Vec3d(points[i].x(),points[i].y(),0.0);
	}
	polyGeom->setVertexArray(vertices);
	polyGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POLYGON, 0, points.size()));

	osg::ref_ptr<osgUtil::Tessellator> tscx = new osgUtil::Tessellator;
	tscx->setTessellationType(osgUtil::Tessellator::TESS_TYPE_GEOMETRY);
	tscx->setBoundaryOnly(false);
	tscx->setWindingType(osgUtil::Tessellator::TESS_WINDING_ODD);
	tscx->retessellatePolygons(*polyGeom);

	
	osg::TriangleFunctor<TriangleResult> tf;
	polyGeom->accept(tf);
	tf.createtriangles(triangles,minarea);
}

double CalcMath::calcArea(const std::vector<osg::Vec3d>& points, osgEarth::MapNode* mapnode)
{
	if (mapnode && mapnode->isGeocentric())
	{
		//https://github.com/kestiny/OSG3D/blob/master/OSGEarth/calcmath.cpp
		double dTotalArea = 0.0;
		int iCount = points.size();
		if (iCount > 2)
		{
			double dLowX = 0.0;
			double dLowY = 0.0;
			double dMiddleX = 0.0;
			double dMiddleY = 0.0;
			double dHighX = 0.0;
			double dHighY = 0.0;
			double AM = 0.0;
			double BM = 0.0;
			double CM = 0.0;
			double AL = 0.0;
			double BL = 0.0;
			double CL = 0.0;
			double AH = 0.0;
			double BH = 0.0;
			double CH = 0.0;

			double dCoefficientL = 0.0;
			double dCoefficientH = 0.0;

			double dALtangent = 0.0;
			double dBLtangent = 0.0;
			double dCLtangent = 0.0;
			double dAHtangent = 0.0;
			double dBHtangent = 0.0;
			double dCHtangent = 0.0;
    
			double dANormalLine = 0.0;
			double dBNormalLine = 0.0;
			double dCNormalLine = 0.0;

			double dOrientationValue = 0.0;
			double dAngleCos = 0.0;

			double dSum1 = 0.0;
			double dSum2 = 0.0;
			int iCount2 = 0;
			int iCount1 = 0;

			double dSum = 0.0;

			for (int i = 0; i < iCount; i++)
			{
				if (i == 0)
				{
					dLowX = osg::DegreesToRadians(points.at(iCount - 1).x());
					dLowY = osg::DegreesToRadians(points.at(iCount - 1).y());
					dMiddleX = osg::DegreesToRadians(points.at(0).x());
					dMiddleY = osg::DegreesToRadians(points.at(0).y());
					dHighX = osg::DegreesToRadians(points.at(1).x());
					dHighY = osg::DegreesToRadians(points.at(1).y());
				}
				else if (i == iCount - 1)
				{
					dLowX = osg::DegreesToRadians(points.at(iCount - 2).x());
					dLowY = osg::DegreesToRadians(points.at(iCount - 2).y());
					dMiddleX = osg::DegreesToRadians(points.at(iCount - 1).x());
					dMiddleY = osg::DegreesToRadians(points.at(iCount - 1).y());
					dHighX = osg::DegreesToRadians(points.at(0).x());
					dHighY = osg::DegreesToRadians(points.at(0).y());
				}
				else
				{
					dLowX = osg::DegreesToRadians(points.at(i - 1).x());
					dLowY = osg::DegreesToRadians(points.at(i - 1).y());
					dMiddleX = osg::DegreesToRadians(points.at(i).x());
					dMiddleY = osg::DegreesToRadians(points.at(i).y());
					dHighX = osg::DegreesToRadians(points.at(i + 1).x());
					dHighY = osg::DegreesToRadians(points.at(i + 1).y());
				}
				AM = cos(dMiddleY) * cos(dMiddleX);
				BM = cos(dMiddleY) * sin(dMiddleX);
				CM = sin(dMiddleY);
				AL = cos(dLowY) * cos(dLowX);
				BL = cos(dLowY) * sin(dLowX);
				CL = sin(dLowY);
				AH = cos(dHighY) * cos(dHighX);
				BH = cos(dHighY) * sin(dHighX);
				CH = sin(dHighY);

				dCoefficientL = (AM*AM + BM*BM + CM*CM) / (AM*AL + BM*BL + CM*CL);
				dCoefficientH = (AM*AM + BM*BM + CM*CM) / (AM*AH + BM*BH + CM*CH);

				dALtangent = dCoefficientL * AL - AM;
				dBLtangent = dCoefficientL * BL - BM;
				dCLtangent = dCoefficientL * CL - CM;
				dAHtangent = dCoefficientH * AH - AM;
				dBHtangent = dCoefficientH * BH - BM;
				dCHtangent = dCoefficientH * CH - CM;

				dAngleCos = (dAHtangent * dALtangent + dBHtangent * dBLtangent + dCHtangent * dCLtangent) /
					(sqrt(dAHtangent * dAHtangent + dBHtangent * dBHtangent + dCHtangent * dCHtangent) *
						sqrt(dALtangent * dALtangent + dBLtangent * dBLtangent + dCLtangent * dCLtangent));

				dAngleCos = acos(dAngleCos);

				dANormalLine = dBHtangent * dCLtangent - dCHtangent * dBLtangent;
				dBNormalLine = 0 - (dAHtangent * dCLtangent - dCHtangent * dALtangent);
				dCNormalLine = dAHtangent * dBLtangent - dBHtangent * dALtangent;

				if (AM != 0)
				{
					dOrientationValue = dANormalLine / AM;
				}
				else if (BM != 0)
				{
					dOrientationValue = dBNormalLine / BM;
				}
				else
				{
					dOrientationValue = dCNormalLine / CM;
				}
				if (dOrientationValue > 0)
				{
					dSum1 += dAngleCos;
					iCount1++;
				}
				else
				{
					dSum2 += dAngleCos;
					iCount2++;
				}
			}
			if (dSum1 > dSum2)
			{
				dSum = dSum1 + (2 * osg::PI*iCount2 - dSum2);
			}
			else
			{
				dSum = (2 * osg::PI*iCount1 - dSum1) + dSum2;
			}

			double r = mapnode->getMapSRS()->getEllipsoid()->getRadiusEquator();
			dTotalArea = (dSum - (iCount - 2)*osg::PI)* r * r;
		}
		return dTotalArea;
	}
	else
	{
		osg::ref_ptr<osgEarth::Features::Polygon> ply = new osgEarth::Features::Polygon(&points);
		return osgEarth::Features::GeometryUtils::getGeometryArea(ply);
	}
}

double CalcMath::calcSurfaceArea(const std::vector<osg::Vec3d>& points, osgEarth::MapNode* mapnode)
{
	double minarea = calcArea(points, 0L);
	minarea /= 100;
	std::vector<std::vector<osg::Vec3d>> triangles;
	trianglation(points, triangles, minarea);

	double surfacearea = 0.0;
	for (size_t i = 0; i < triangles.size(); i++)
	{
		osg::Vec3d p0 = triangles[i][0];
		osg::Vec3d p1 = triangles[i][1];
		osg::Vec3d p2 = triangles[i][2];
		mapnode->getTerrain()->getHeight(NULL, p0.x(), p0.y(), &(p0.z()),NULL);
		mapnode->getTerrain()->getHeight(NULL, p1.x(), p1.y(), &(p1.z()), NULL);
		mapnode->getTerrain()->getHeight(NULL, p2.x(), p2.y(), &(p2.z()), NULL);
		p0 = latlnghigh2xyz(mapnode, p0);
		p1 = latlnghigh2xyz(mapnode, p1);
		p2 = latlnghigh2xyz(mapnode, p2);
		
		surfacearea += caltrianglearea(p0, p1, p2);
	}

	return surfacearea;
}

double CalcMath::calcRhumbArea(const std::vector<osg::Vec3d>& points, osgEarth::MapNode* mapnode, unsigned int parts)
{
	if (!mapnode || !mapnode->isGeocentric() || points.size()<=2)
		return 0.0;

	double step = 1.0 / double(parts);

	std::vector<osg::Vec3d> temppoints;
	temppoints.push_back(points[0]);
	for (size_t i = 0; i < points.size()-1; i++)
	{
		osg::Vec3d p0 = points[i];
		osg::Vec3d p1 = points[i + 1];
		double zdelta = p1.z() - p0.z();
		
		for (unsigned i = 1; i <= parts; ++i)
		{
			double t = step*double(i);
			osg::Vec3d p;

			double lat1 = osg::DegreesToRadians(p0.y()), lon1 = osg::DegreesToRadians(p0.x());
			double lat2 = osg::DegreesToRadians(p1.y()), lon2 = osg::DegreesToRadians(p1.x());

			double totalDistance = osgEarth::GeoMath::rhumbDistance(lat1, lon1, lat2, lon2);
			double bearing = osgEarth::GeoMath::rhumbBearing(lat1, lon1, lat2, lon2);

			double interpDistance = t * totalDistance;

			double lat3, lon3;
			osgEarth::GeoMath::rhumbDestination(lat1, lon1, bearing, interpDistance, lat3, lon3);

			p.set(osg::RadiansToDegrees(lon3), osg::RadiansToDegrees(lat3), p0.z() + t*zdelta);

			temppoints.push_back(p);
		}
	}

	return calcArea(temppoints, mapnode);
}

double CalcMath::calcRhumbSurfaceArea(const std::vector<osg::Vec3d>& points, osgEarth::MapNode* mapnode, unsigned int parts)
{
	if (!mapnode || !mapnode->isGeocentric() || points.size() <= 2)
		return 0.0;

	double step = 1.0 / double(parts);

	std::vector<osg::Vec3d> temppoints;
	temppoints.push_back(points[0]);
	for (size_t i = 0; i < points.size() - 1; i++)
	{
		osg::Vec3d p0 = points[i];
		osg::Vec3d p1 = points[i + 1];
		double zdelta = p1.z() - p0.z();

		for (unsigned i = 1; i <= parts; ++i)
		{
			double t = step*double(i);
			osg::Vec3d p;

			double lat1 = osg::DegreesToRadians(p0.y()), lon1 = osg::DegreesToRadians(p0.x());
			double lat2 = osg::DegreesToRadians(p1.y()), lon2 = osg::DegreesToRadians(p1.x());

			double totalDistance = osgEarth::GeoMath::rhumbDistance(lat1, lon1, lat2, lon2);
			double bearing = osgEarth::GeoMath::rhumbBearing(lat1, lon1, lat2, lon2);

			double interpDistance = t * totalDistance;

			double lat3, lon3;
			osgEarth::GeoMath::rhumbDestination(lat1, lon1, bearing, interpDistance, lat3, lon3);

			p.set(osg::RadiansToDegrees(lon3), osg::RadiansToDegrees(lat3), p0.z() + t*zdelta);

			temppoints.push_back(p);
		}
	}

	return calcRhumbSurfaceArea(temppoints, mapnode);
}

double CalcMath::calcVolume(const std::vector<osg::Vec3d>& points, osgEarth::MapNode* mapnode, double deep)
{
	double minarea = calcArea(points, mapnode);
	minarea /= 100;
	std::vector<std::vector<osg::Vec3d>> triangles;
	trianglation(points, triangles, minarea);

	double volume = 0.0;
	for (size_t i = 0; i < triangles.size(); i++)
	{
		osg::Vec3d p0 = triangles[i][0];
		osg::Vec3d p1 = triangles[i][1];
		osg::Vec3d p2 = triangles[i][2];
		mapnode->getTerrain()->getHeight(NULL, p0.x(), p0.y(), &(p0.z()), NULL);
		mapnode->getTerrain()->getHeight(NULL, p1.x(), p1.y(), &(p1.z()), NULL);
		mapnode->getTerrain()->getHeight(NULL, p2.x(), p2.y(), &(p2.z()), NULL);
		p0 = latlnghigh2xyz(mapnode, p0);
		p1 = latlnghigh2xyz(mapnode, p1);
		p2 = latlnghigh2xyz(mapnode, p2);

		volume += caltrianglearea(p0, p1, p2)*deep;
	}

	return volume;
}

double CalcMath::calcRhumbVolume(const std::vector<osg::Vec3d>& points, osgEarth::MapNode* mapnode, double deep, unsigned int parts /*= 100*/)
{
	if (!mapnode || !mapnode->isGeocentric() || points.size() <= 2)
		return 0.0;

	double step = 1.0 / double(parts);

	std::vector<osg::Vec3d> temppoints;
	temppoints.push_back(points[0]);
	for (size_t i = 0; i < points.size() - 1; i++)
	{
		osg::Vec3d p0 = points[i];
		osg::Vec3d p1 = points[i + 1];
		double zdelta = p1.z() - p0.z();

		for (unsigned i = 1; i <= parts; ++i)
		{
			double t = step*double(i);
			osg::Vec3d p;

			double lat1 = osg::DegreesToRadians(p0.y()), lon1 = osg::DegreesToRadians(p0.x());
			double lat2 = osg::DegreesToRadians(p1.y()), lon2 = osg::DegreesToRadians(p1.x());

			double totalDistance = osgEarth::GeoMath::rhumbDistance(lat1, lon1, lat2, lon2);
			double bearing = osgEarth::GeoMath::rhumbBearing(lat1, lon1, lat2, lon2);

			double interpDistance = t * totalDistance;

			double lat3, lon3;
			osgEarth::GeoMath::rhumbDestination(lat1, lon1, bearing, interpDistance, lat3, lon3);

			p.set(osg::RadiansToDegrees(lon3), osg::RadiansToDegrees(lat3), p0.z() + t*zdelta);

			temppoints.push_back(p);
		}
	}

	return calcVolume(temppoints, mapnode,deep);
}

osg::Vec3d CalcMath::latlnghigh2xyz(osgEarth::MapNode* mapnode, const osg::Vec3d& llh)
{
	osg::Vec3d res;
	double lat = osg::DegreesToRadians(llh.y());
	double lng = osg::DegreesToRadians(llh.x());;
	double height = llh.z();
	mapnode->getMap()->getProfile()->getSRS()->getEllipsoid()->convertLatLongHeightToXYZ(
		lat, lng, height, res.x(), res.y(), res.z());
	return res;
}

osg::Vec3d CalcMath::xyz2latlnghigh(osgEarth::MapNode* mapnode, const osg::Vec3d& xyz)
{
	double lat = 0.0;
	double lng = 0.0;
	double height = 0.0;
	mapnode->getMap()->getProfile()->getSRS()->getEllipsoid()->convertXYZToLatLongHeight(
		xyz.x(), xyz.y(), xyz.z(), lat, lng, height);
	osg::Vec3d res;
	res.x() = osg::RadiansToDegrees(lng);
	res.y() = osg::RadiansToDegrees(lat);
	res.z() = height;
	return res;
}


double CalcMath::caltrianglearea(const osg::Vec3d& a, const osg::Vec3d& b, const osg::Vec3d& c)
{
	double area = 0;

	double side[3];

	side[0] = sqrt(pow(a.x() - b.x(), 2) + pow(a.y() - b.y(), 2) + pow(a.z() - b.z(), 2));
	side[1] = sqrt(pow(a.x() - c.x(), 2) + pow(a.y() - c.y(), 2) + pow(a.z() - c.z(), 2));
	side[2] = sqrt(pow(c.x() - b.x(), 2) + pow(c.y() - b.y(), 2) + pow(c.z() - b.z(), 2));

	if (side[0] + side[1] <= side[2] || side[0] + side[2] <= side[1] || side[1] + side[2] <= side[0]) return area;

	double p = (side[0] + side[1] + side[2]) / 2;
	area = sqrt(p*(p - side[0])*(p - side[1])*(p - side[2]));

	return area;
}