#pragma once

#include "oepExtension.h"

using namespace System;
using namespace System::Collections::Generic;

namespace gEarthPack
{
	public interface class IoepExtensionCreator
	{
		String^ supportType();
		oepExtension^ createExtenson(IntPtr param);
	};

	public ref class oepExtensionFactory
	{
	public:
		static oepExtensionFactory();

	public:

		static void registerCreator(IoepExtensionCreator^ creator);
		static void unregisterCreator(String^ type);

		static oepExtension^ creatorExtenson(String^ type, IntPtr param);

	internal:

		static osgEarth::Extension* createoeExtension(const osgEarth::Config& config);

	private:

		static Dictionary<String^, IoepExtensionCreator^>^ _creatorcache;

	};
}


