#pragma once
#include "oepEventHandler.h"
namespace gEarthPack
{
	public ref class oepMeasureVolumeHander :
		public oepEventHandler
	{
	public:
		oepMeasureVolumeHander();

	public:

		property double Volume
		{
			double get();
		internal:
			void set(double v);
		}

		property double Deep
		{
			double get();
			void set(double v);
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

		double _volume;
		unsigned int _nodemask;
	};

}