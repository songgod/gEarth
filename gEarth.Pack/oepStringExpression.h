#pragma once
#include "oepValObject.h"
namespace gEarthPack
{
	public ref class oepStringExpression :
		public oepValObject<osgEarth::Symbology::StringExpression>
	{
	public:
		oepStringExpression();

	public:

		property String^ Infix
		{
			String^ get();
			void set(String^ p);
		}

		property String^ Literal
		{
			String^ get();
			void set(String^ p);
		}

		property bool IsEmpty
		{
			bool get();
		}

	private:


	};
}

