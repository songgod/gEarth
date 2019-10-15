#pragma once
#include "oepEventHandler.h"
#include "oepMap.h"

namespace gEarthPack
{
	public ref class oepMeasureDistanceHeightHandler :
		public oepEventHandler
	{
	public:
		oepMeasureDistanceHeightHandler();

	public:

		property double Distance
		{
			double get();
		internal:
			void set(double d);
		}

		property double Height
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
		double _height;
		unsigned int _nodemask;
	};
}

