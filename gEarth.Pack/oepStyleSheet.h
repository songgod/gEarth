#pragma once
#include "oepRefObject.h"
#include "oepStyle.h"
#include "oepStyleSelector.h"
#include "oepResourceLibrary.h"

namespace gEarthPack
{
	public ref class oepStyleSheet :
		public oepRefObject
	{
	public:
		oepStyleSheet();

	public:

		ref class oepScriptDef : oepRefObject
		{
		public:

			oepScriptDef();

		public:

			virtual property String^ Name
			{
				String^ get() override;
				void set(String^ p) override;
			}

			property String^ Code
			{
				String^ get();
				void set(String^ p);
			}

			property String^ Language
			{
				String^ get();
				void set(String^ p);
			}

			property String^ Profile
			{
				String^ get();
				void set(String^ p);
			}

			property String^ Url
			{
				String^ get();
				void set(String^ p);
			}
		};

	public:

		virtual property String^ Name
		{
			String^ get() override;
			void set(String^ p) override;
		}

		property oepStyleMap^ StyleMap
		{
			oepStyleMap^ get();
			void set(oepStyleMap^ p);
		}

		property oepStyle^ DefaultStyle
		{
			oepStyle^ get();
		}

		property oepStyleSelectorList^ Selectors
		{
			oepStyleSelectorList^ get();
			void set(oepStyleSelectorList^ p);
		}

		property oepResourceLibraryMap^ Resources
		{
			oepResourceLibraryMap^ get();
			void set(oepResourceLibraryMap^ p);
		}

		property oepScriptDef^ Script
		{
			oepScriptDef^ get();
			void set(oepScriptDef^ p);
		}

	internal:

		virtual void binded() override;
		virtual void unbinded() override;

	protected:

		void OnResourceCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e);

	private:

		oepStyleMap^ _stylemap;
		oepStyleSelectorList^ _selectors;
		oepResourceLibraryMap^ _resLibs;
		oepScriptDef^ _script;
	};
}


