#pragma once
#include "oepSymbol.h"
#include "oepNumericExpression.h"
namespace gEarthPack
{
	public ref class oepAltitudeSymbol :
		public oepSymbol
	{
	public:
		oepAltitudeSymbol();

	public:

		enum class oepClamping
		{
			ClampNone,
			ClampToTerrain,
			ClampRelativeToTerrain,
			ClampAbsolute
		};

		enum class oepTechnique
		{
			TechniqueMap,
			TechniqueScene,
			TechniqueGpu,
			TechniqueDrape
		};

		enum class oepBinding
		{
			BindingVertex,
			BindingCentroid
		};

	public:

		property oepClamping Clamping
		{
			oepClamping get();
			void set(oepClamping p);
		}

		property oepTechnique Techinique
		{
			oepTechnique get();
			void set(oepTechnique p);
		}

		property oepBinding Binding
		{
			oepBinding get();
			void set(oepBinding p);
		}

		property float ClampingResolution
		{
			float get();
			void set(float p);
		}

		property oepNumericExpression^ VerticalOffset
		{
			oepNumericExpression^ get();
			void set(oepNumericExpression^ p);
		}

		property oepNumericExpression^ VerticalScale
		{
			oepNumericExpression^ get();
			void set(oepNumericExpression^ p);
		}

	internal:

		virtual void binded() override;
		virtual void unbinded() override;

	private:

		oepNumericExpression^ _verticalOffset;
		oepNumericExpression^ _verticalScale;
	};
}

