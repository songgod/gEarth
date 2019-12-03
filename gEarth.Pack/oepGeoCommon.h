#pragma once

namespace gEarthPack
{
	public enum class oepGeoInterpolation : char 
	{
		GreatCircle,
		RhumbLine
	};

	public enum class oepResampleMode : char
	{
		ResampleLinear,
		ResampleGreatcircle,
		ResampleRhumb
	};

	public enum class oepShaderPolicy : char
	{
		ShaderpolicyDisable,
		ShaderpolicyGenerate,
		ShaderpolicyInherit
	};
}

