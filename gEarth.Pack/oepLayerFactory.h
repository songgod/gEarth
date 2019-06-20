#pragma once

#include "oepLayer.h"

using namespace System;
using namespace System::Collections::Generic;

namespace gEarthPack
{
	public interface class ILayerCreator
	{
		String^ supportType();
		oepLayer^ createLayer(IntPtr param);
	};

	public ref class oepLayerFactory
	{
	public:
		static oepLayerFactory();

	public:

		static void registerCreator(ILayerCreator^ creator);
		static void unregisterCreator(String^ type);

		static oepLayer^ creatorLayer(String^ type, IntPtr param);

	private:

		static Dictionary<String^, ILayerCreator^>^ _creatorcache;

	};
}
