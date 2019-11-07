#pragma once
#include "oepEventHandler.h"
#include "oepVector.h"
namespace gEarthPack
{
	public ref class oepMeasureSlopeAspectHandler :
		public oepEventHandler
	{
	public:
		oepMeasureSlopeAspectHandler();

	public:

		property double Slope
		{
			double get();
		internal:
			void set(double a);
		}

		property double Aspect
		{
			double get();
		internal:
			void set(double b);
		}

		property oepVec3f Point
		{
			oepVec3f get();
		internal:
			void set(oepVec3f p);
		}

	internal:
		virtual void bind(osgEarth::MapNode* pMapNode) override;
		virtual void unbind(osgEarth::MapNode* pMapNode) override;

	private:

		double _slope;
		double _aspect;
		oepVec3f _point;
		unsigned int _nodemask;
	};
}

