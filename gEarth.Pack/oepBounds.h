#pragma once
#include "oepValObject.h"

using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	public ref class oepBounds :
		public oepValObject
	{
	public:
		oepBounds();

	public:

		property double Xmin
		{
			double get();
			void set(double p);
		}

		property double Ymin
		{
			double get();
			void set(double p);
		}

		property double Zmin
		{
			double get();
			void set(double p);
		}

		property double Xmax
		{
			double get();
			void set(double p);
		}

		property double Ymax
		{
			double get();
			void set(double p);
		}

		property double Zmax
		{
			double get();
			void set(double p);
		}

		property double Width
		{
			double get();
		}

		property double Height
		{
			double get();
		}

		property double Depth
		{
			double get();
		}

	internal:

		virtual void delelehandle() override;

	internal:

		osgEarth::Bounds* ntBounds() { return as<osgEarth::Bounds>(); }
	};

	public ref class oepBoundsCollection : public ObservableCollection<oepBounds^>
	{

	};
}
