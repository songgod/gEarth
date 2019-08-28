#pragma once
#include "oepExtension.h"
#include "oepAnimationPath.h"

namespace gEarthPack
{
	public ref class oepAnimationPathExtension :
		public oepExtension
	{
	public:
		oepAnimationPathExtension();

	public:

		property oepAnimationPaths^ AnimationPaths
		{
			oepAnimationPaths^ get();
		}

	internal:
		oepAnimationPathExtension(osgEarth::Extension* ext);

	private:

		void init();
		void OnAnimationPathCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e);

	private:

		oepAnimationPaths^ _animationpaths;
	};
}