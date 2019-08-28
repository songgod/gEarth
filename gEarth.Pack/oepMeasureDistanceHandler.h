#pragma once
#include "oepEventHandler.h"
#include "oepMap.h"

namespace gEarthPack
{
	public ref class oepMeasureDistanceHandler :
		public oepEventHandler
	{
	public:
		oepMeasureDistanceHandler();

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
		virtual void bind(osgEarth::MapNode* pMapNode) override;
		virtual void unbind(osgEarth::MapNode* pMapNode) override;

	private:

		double _distance;
		unsigned int _nodemask;
	};
}

