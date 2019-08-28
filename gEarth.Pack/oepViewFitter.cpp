#include "stdafx.h"
#include "Viewer.h"
#include "oepViewFitter.h"

using namespace gEarthPack;

static oepViewFitter::oepViewFitter()
{
}

oepViewpoint^ oepViewFitter::Fitter(oepLayer^ layer, oepMap^ map, oepRender^ render)
{
	if (layer == nullptr || map==nullptr || render == nullptr)
		return nullptr;

	osgEarth::Layer* pLayer = layer->ref();
	if (pLayer == nullptr)
		return nullptr;

	osgEarth::Map* pMap = map->getMap();
	if (!pMap)
		return nullptr;

	const osgEarth::GeoExtent& extent = pLayer->getExtent();
	if (extent.isValid())
	{
		std::vector <osgEarth::GeoPoint > points;
		points.push_back(osgEarth::GeoPoint(extent.getSRS(), extent.west(), extent.south()));
		points.push_back(osgEarth::GeoPoint(extent.getSRS(), extent.east(), extent.north()));

		osgEarth::Util::ViewFitter fitter(pMap->getSRS(), render->_viewer->getViewer()->getCamera());
		osgEarth::Viewpoint vp;
		if (fitter.createViewpoint(points, vp))
		{
			return gcnew oepViewpoint(vp);
		}
	}
	else if (pLayer->getNode())
	{
		const osg::BoundingSphere& bs = pLayer->getNode()->getBound();
		if (bs.valid())
		{
			osg::Vec3d c = bs.center();
			double r = bs.radius();
			const osgEarth::SpatialReference* mapSRS = pMap->getSRS();

			std::vector<osgEarth::GeoPoint> points;
			osgEarth::GeoPoint p;
			p.fromWorld(mapSRS, osg::Vec3d(c.x() + r, c.y(), c.z())); points.push_back(p);
			p.fromWorld(mapSRS, osg::Vec3d(c.x() - r, c.y(), c.z())); points.push_back(p);
			p.fromWorld(mapSRS, osg::Vec3d(c.x(), c.y() + r, c.z())); points.push_back(p);
			p.fromWorld(mapSRS, osg::Vec3d(c.x(), c.y() - r, c.z())); points.push_back(p);
			p.fromWorld(mapSRS, osg::Vec3d(c.x(), c.y(), c.z() + r)); points.push_back(p);
			p.fromWorld(mapSRS, osg::Vec3d(c.x(), c.y(), c.z() - r)); points.push_back(p);

			osgEarth::Util::ViewFitter fitter(pMap->getSRS(), render->_viewer->getViewer()->getCamera());
			osgEarth::Viewpoint vp;
			if (fitter.createViewpoint(points, vp))
			{
				return gcnew oepViewpoint(vp);
			}
		}
	}

	return nullptr;
}
