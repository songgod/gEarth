#include "stdafx.h"
#include "oepUtil.h"

using namespace gEarthPack;

String^ gEarthPack::Str2Cli(const std::string& str)
{
	return marshal_as<String^>(str);
}

std::string gEarthPack::Str2Std(String^ str)
{
	return marshal_as<std::string>(str);
}