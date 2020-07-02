#pragma once
#include "oepValObject.h"

using namespace osgEarth::Symbology;

namespace gEarthPack
{
	public ref class oepStringExpression :
		public oepValObject
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
		
	internal:

		virtual void delelehandle() override;

	internal:

		StringExpression* ntStringExpression() {
			return as<StringExpression>();
		}

	private:


	};
}

