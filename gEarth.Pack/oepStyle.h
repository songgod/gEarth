#pragma once
#include "oepValObject.h"
#include "oepValMap.h"
#include "oepSymbol.h"

namespace gEarthPack
{
	public ref class oepStyle :
		public oepValObject
	{
	public:
		oepStyle();

	public:

		property String^ Name
		{
			String^ get() override;
			void set(String^ p) override;
		}

		property bool IsEmpty
		{
			bool get();
		}

		property oepSymbolCollection^ Symbols
		{
			oepSymbolCollection^ get();
			void set(oepSymbolCollection^ p);
		}


	public:

		oepStyle^ combineWith(oepStyle^ style);

	public:

		virtual void binded() override;
		virtual void unbinded() override;
		virtual void delelehandle() override;

	protected:

		void OnMTCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e);

	private:

		oepSymbolCollection^ _symbols;
	};

	public ref class oepStyleMap : oepValMap<String^, oepStyle^, std::string, osgEarth::Symbology::Style>
	{
	public:
		oepStyleMap(){}

	internal:

		virtual oepStyle^ NewMValue() override;
		virtual String^ LKey2MKey(std::string key) override;
		virtual std::string MKey2LKey(String^ key) override;
	};
}


