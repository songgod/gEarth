#pragma once
#include "oepEventHandler.h"
#include "oepVector.h"

using namespace System::Collections::Generic;

namespace gEarthPack
{
	public ref class oepMeasureProfileHandler :
		public oepEventHandler
	{
	public:
		oepMeasureProfileHandler();

	public:

		property double TotalDistance
		{
			double get();
		internal:
			void set(double v);
		}

		property double MinElevation
		{
			double get();
		internal:
			void set(double v);
		}

		property double MaxElevation
		{
			double get();
		internal:
			void set(double v);
		}

		property List<oepVec2f>^ Profiles
		{
			List<oepVec2f>^ get();
		internal:
			void set(List<oepVec2f>^ v);
		}

	internal:
		virtual void bind(osgEarth::MapNode* pMapNode) override;
		virtual void unbind(osgEarth::MapNode* pMapNode) override;

	private:

		double _totaldistance;
		double _minelevation;
		double _maxelevation;
		unsigned int _nodemask;
		List<oepVec2f>^ _profile;
	};
}
