#include "stdafx.h"
#include "oepStyleSheet.h"

using namespace gEarthPack;
using namespace osgEarth::Symbology;


oepStyleSheet::oepStyleSheet()
{
	bind(new StyleSheet());
}

oepStyleSheet::oepScriptDef::oepScriptDef()
{
	bind(new StyleSheet::ScriptDef());
}

String^ oepStyleSheet::oepScriptDef::Name::get()
{
	return Str2Cli(ref()->name);
}

void oepStyleSheet::oepScriptDef::Name::set(String^ s)
{
	ref()->name = Str2Std(s);
	NotifyChanged("Name");
}

String^ oepStyleSheet::oepScriptDef::Code::get()
{
	return Str2Cli(ref()->code);
}

void oepStyleSheet::oepScriptDef::Code::set(String^ s)
{
	ref()->code = Str2Std(s);
	NotifyChanged("Code");
}

String^ oepStyleSheet::oepScriptDef::Language::get()
{
	return Str2Cli(ref()->language);
}

void oepStyleSheet::oepScriptDef::Language::set(String^ s)
{
	ref()->language = Str2Std(s);
	NotifyChanged("Language");
}

String^ oepStyleSheet::oepScriptDef::Profile::get()
{
	return Str2Cli(ref()->profile);
}

void oepStyleSheet::oepScriptDef::Profile::set(String^ s)
{
	ref()->profile = Str2Std(s);
	NotifyChanged("Profile");
}

String^ oepStyleSheet::oepScriptDef::Url::get()
{
	return Str2Cli(ref()->uri.value().full());
}

void oepStyleSheet::oepScriptDef::Url::set(String^ s)
{
	ref()->uri.mutable_value() = Str2Std(s);
	NotifyChanged("Url");
}

String^ oepStyleSheet::Name::get()
{
	return Str2Cli(ref()->name().value());
}

void oepStyleSheet::Name::set(String^ s)
{
	ref()->name() = Str2Std(s);
	NotifyChanged("Name");
}

oepStyleMap^ oepStyleSheet::Styles::get()
{
	return _stylemap;
}

void oepStyleSheet::Styles::set(oepStyleMap^ s)
{
	StyleSheet* to = as<StyleSheet>();
	if (to != NULL && s != nullptr)
	{
		to->styles() = *(s->Val());
	}
	NotifyChanged("Styles");
}

oepStyle^ oepStyleSheet::DefaultStyle::get()
{
	oepStyle^ res = gcnew oepStyle();
	res->bind(ref()->getDefaultStyle(),false);
	return res;
}

oepStyleSelectorList^ oepStyleSheet::Selectors::get()
{
	return _selectors;
}

void oepStyleSheet::Selectors::set(oepStyleSelectorList^ s)
{
	StyleSheet* to = as<StyleSheet>();
	if (to != NULL && s != nullptr)
	{
		to->selectors() = *(s->Val());
	}
	NotifyChanged("Selectors");
}

oepResourceLibraryMap^ oepStyleSheet::Resources::get()
{
	return _resLibs;
}

void oepStyleSheet::Resources::set(oepResourceLibraryMap^ s)
{
	_resLibs = s;
	ref()->ClearResourceLibrary();
	for each (oepResourceLibrary^ r in s)
	{
		ref()->addResourceLibrary(r->ref());
	}
	NotifyChanged("Resources");
}

oepStyleSheet::oepScriptDef^ oepStyleSheet::Script::get()
{
	return _script;
}

void oepStyleSheet::Script::set(oepStyleSheet::oepScriptDef^ s)
{
	_script = s;
	ref()->setScript(_script->ref());
	NotifyChanged("Script");
}

void gEarthPack::oepStyleSheet::binded()
{
	_stylemap = gcnew oepStyleMap();
	_stylemap->bind(&(ref()->styles()),false);
	_selectors = gcnew oepStyleSelectorList();
	_selectors->bind(&(ref()->selectors()),false);
	_script = gcnew oepScriptDef();
	_script->bind(ref()->script());
	_resLibs = gcnew oepResourceLibraryMap();
	std::vector<std::string> names = ref()->getResourceNames();
	for (size_t i = 0; i < names.size(); i++)
	{
		oepResourceLibrary^ r = gcnew oepResourceLibrary("","");
		r->bind(ref()->getResourceLibrary(names[i]));
	}
	_resLibs->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &gEarthPack::oepStyleSheet::OnResourceCollectionChanged);
}

void gEarthPack::oepStyleSheet::unbinded()
{
	_stylemap->unbind();
	_selectors->unbind();
	_script->unbind();
}

void oepStyleSheet::OnResourceCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e)
{
	switch (e->Action)
	{
	case System::Collections::Specialized::NotifyCollectionChangedAction::Add:
	{
		if (e->NewItems != nullptr && e->NewItems->Count > 0)
		{
			for (int i = 0; i < e->NewItems->Count; i++)
			{
				oepResourceLibrary^ r = dynamic_cast<oepResourceLibrary^>(e->NewItems[i]);
				if (r != nullptr)
				{
					ref()->addResourceLibrary(r->ref());
				}
			}
		}
		break;
	}
	case System::Collections::Specialized::NotifyCollectionChangedAction::Remove:
	{
		if (e->OldItems != nullptr && e->OldItems->Count > 0)
		{
			for (int i = 0; i < e->OldItems->Count; i++)
			{
				oepResourceLibrary^ r = dynamic_cast<oepResourceLibrary^>(e->NewItems[i]);
				if (r != nullptr)
				{
					ref()->removeResourceLibrary(r->ref());
				}
			}
		}
		break;
	}
	case System::Collections::Specialized::NotifyCollectionChangedAction::Replace:
	{
		throw gcnew NotImplementedException();
		break;
	}
	case System::Collections::Specialized::NotifyCollectionChangedAction::Move:
	{
		throw gcnew NotImplementedException();
		break;
	}
	case System::Collections::Specialized::NotifyCollectionChangedAction::Reset:
	{
		ref()->ClearResourceLibrary();
		break;
	}
	default:
		break;
	}
}
