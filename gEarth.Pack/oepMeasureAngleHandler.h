#pragma once

#include "oepEventHandler.h"
namespace gEarthPack
{
	public ref class oepMeasureAngleHandler :
		public oepEventHandler
	{
	public:
		oepMeasureAngleHandler();

	public:

		property double Angle
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
		virtual void bind(osgEarth::MapNode* pMapNode) override;
		virtual void unbind(osgEarth::MapNode* pMapNode) override;

	private:

		double _angle;
		unsigned int _nodemask;
	};
}

