#pragma once
#include "oepValObject.h"
#include "oepValList.h"
#include "oepStringExpression.h"
#include "oepQuery.h"

namespace gEarthPack
{
	public ref class oepStyleSelector :
		public oepValObject<osgEarth::Symbology::StyleSelector>
	{
	public:
		oepStyleSelector();

	public:

		virtual property String^ Name
		{
			String^ get() override;
			void set(String^ p) override;
		}

		property String^ StyleName
		{
			String^ get();
			void set(String^ p);
		}

		property oepStringExpression^ StyleExpression
		{
			oepStringExpression^ get();
			void set(oepStringExpression^ p);
		}

		property oepQuery^ Query
		{
			oepQuery^ get();
			void set(oepQuery^ p);
		}


		property String^ SelectStyleName
		{
			String^ get();
		}

	public:

		virtual void binded() override;
		virtual void unbinded() override;

	private:

		oepStringExpression^ _styleExpression;
		oepQuery^ _query;
	};

	public ref class oepStyleSelectorList : public oepValList<oepStyleSelector, osgEarth::Symbology::StyleSelector>
	{
		
	};
}

