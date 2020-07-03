#pragma once
#include "oepRefObject.h"
#include "oepStringExpression.h"

using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	public ref class oepSymbol :
		public oepRefObject
	{
	public:

		property oepStringExpression^ Script
		{
			oepStringExpression^ get();
			void set(oepStringExpression^ p);
		}

	internal:

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

