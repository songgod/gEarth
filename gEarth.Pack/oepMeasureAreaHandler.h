#pragma once
#include "oepEventHandler.h"

namespace gEarthPack
{
	class MeasureAreaHandler;
	public ref class oepMeasureAreaHandler :
		public oepEventHandler
	{
	public:
		oepMeasureAreaHandler();

	public:

		property double Area
		{
			double get();
		internal:
			void set(double a);
		}

		property bool bGreatCircle
		{
			bool get();
			void set(bool b);
		}

	internal:
		MeasureAreaHandler* asMesureAreaHandler();
		virtual void bind(osgEarth::MapNode* pMapNode) override;
		virtual void unbind(osgEarth::MapNode* pMapNode) override;

	private:

		double _area;
		unsigned int _nodemask;
	};
}

