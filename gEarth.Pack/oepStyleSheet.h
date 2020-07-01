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

		internal:

			osgEarth::StyleSheet::ScriptDef* ntScriptDef() { return as<osgEarth::StyleSheet::ScriptDef>(); }

		};

	public:

		virtual property String^ Name
		{
			String^ get() override;
			void set(String^ p) override;
		}

		property oepStyleMap^ Styles
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

	internal:

		osgEarth::Symbology::StyleSheet* ntStyleSheet() {
			return as<osgEarth::Symbology::StyleSheet>();
		}

	protected:

		void OnResourceCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e);

	private:

		oepStyleMap^ _stylemap;
		oepStyleSelectorList^ _selectors;
		oepResourceLibraryMap^ _resLibs;
		oepScriptDef^ _script;
	};
}


