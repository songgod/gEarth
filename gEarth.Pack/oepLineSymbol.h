#pragma once
#include "oepSymbol.h"
#include "oepStroke.h"
#include "oepStringExpression.h"

namespace gEarthPack
{
	public ref class oepLineSymbol :
		public oepSymbol
	{
	public:
		oepLineSymbol();

	public:

		property oepStroke^ Stroke
		{
			oepStroke^ get();
			void set(oepStroke^ p);
		}

		property double TessellationSize
		{
			double get();
			void set(double p);
		}

		property unsigned int Tessellation
		{
			unsigned int get();
			void set(unsigned int p);
		}

		property float CreaseAngle
		{
			float get();
			void set(float p);
		}

		property oepStringExpression^ ImageURI
		{
			oepStringExpression^ get();
			void set(oepStringExpression^ p);
		}


	internal:

		virtual void binded() override;
		virtual void unbinded() override;

	private:

		oepStroke^ _stroke;
		oepStringExpression^ _imageurl;
	};
}

