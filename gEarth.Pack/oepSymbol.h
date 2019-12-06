#pragma once
#include "oepRefObject.h"
#include "oepStringExpression.h"

using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	public ref class oepSymbol :
		public oepRefObject<osgEarth::Symbology::Symbol>
	{
	public:

		property oepStringExpression^ Script
		{
			oepStringExpression^ get();
			void set(oepStringExpression^ p);
		}

	public:

		virtual void binded() override;
		virtual void unbinded() override;

	protected:
		oepSymbol();

	private:

		oepStringExpression^ _script;
	};


	public ref class oepSymbolCollection : public ObservableCollection<oepSymbol^>
	{

	};
}

