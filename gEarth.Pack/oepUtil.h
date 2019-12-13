#pragma once

using namespace System;
using namespace System::Collections::ObjectModel;
using namespace msclr::interop;

namespace gEarthPack
{
	String^ Str2Cli(const std::string& str);

	std::string Str2Std(String^ str);
}

