#pragma once
#include "oepSymbol.h"
#include "oepNumericExpression.h"
#include "oepDepthOffsetOptions.h"

namespace gEarthPack
{
	public ref class oepRenderSymbol :
		public oepSymbol
	{
	public:
		oepRenderSymbol();

	public:

		property bool DepthTest
		{
			bool get();
			void set(bool p);
		}

		property bool Lighting
		{
			bool get();
			void set(bool p);
		}

		property bool BackfaceCulling
		{
			bool get();
			void set(bool p);
		}

		property oepNumericExpression^ Order
		{
			oepNumericExpression^ get();
			void set(oepNumericExpression^ p);
		}

		property unsigned int ClipPlane
		{
			unsigned int get();
			void set(unsigned int p);
		}
		
		property float MinAlpha
		{
			float get();
			void set(float p);
		}

		property bool Transparent
		{
			bool get();
			void set(bool p);
		}

		property String^ RenderBin
		{
			String^ get();
			void set(String^ p);
		}

		property bool Decal
		{
			bool get();
			void set(bool p);
		}

		property double MaxCreaseAngle
		{
			double get();
			void set(double p);
		}

		property double MaxAltitude
		{
			double get();
			void set(double p);
		}
			
		property oepDepthOffsetOptions^ DepthOffset
		{
			oepDepthOffsetOptions^ get();
			void set(oepDepthOffsetOptions^ p);
		}

	internal:

		virtual void binded() override;
		virtual void unbinded() override;

	protected:

		oepDepthOffsetOptions^ _depthoffset;
		oepNumericExpression^ _order;
	};
}

