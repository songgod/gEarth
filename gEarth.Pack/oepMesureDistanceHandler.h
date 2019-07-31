#pragma once
#include "oepEventHandler.h"
#include "oepMap.h"
#include <osgEarthUtil/MeasureTool>

using namespace osgEarth::Util;

namespace gEarthPack
{
	public ref class oepMesureDistanceHandler :
		public oepEventHandler
	{
	public:
		oepMesureDistanceHandler();

	public:

		property double Distance
		{
			double get();
		internal:
			void set(double d);
		}

		property bool bPath
		{
			bool get();
			void set(bool b);
		}

		property bool bGreatCircle
		{
			bool get();
			void set(bool b);
		}

	internal:
		MeasureToolHandler* asMesureDistanceHandler();
		virtual void setMapNode(osgEarth::MapNode* pMapNode) override;
		virtual osgEarth::MapNode* getMapNode() override;
		virtual void quit() override;

	private:

		double _distance;
		unsigned int _nodemask;
	};
}

