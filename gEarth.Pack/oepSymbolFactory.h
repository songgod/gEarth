#pragma once

#include "oepSymbol.h"

using namespace System;
using namespace System::Collections::Generic;

namespace gEarthPack
{
	public interface class IoepSymbolCreator
	{
		String^ supportType();
		oepSymbol^ createSymbol(IntPtr param);
	};

	public ref class oepSymbolFactory
	{
	public:
		static oepSymbolFactory();

	public:

		static void registerCreator(IoepSymbolCreator^ creator);
		static void unregisterCreator(String^ type);

		static oepSymbol^ creatorSymbol(String^ type, IntPtr param);

	private:

		typedef Dictionary<String^, IoepSymbolCreator^> DicSymbolCreator;
		static DicSymbolCreator^ _symbolcreatorcache;
	};
}
