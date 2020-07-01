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
	return Str2Cli(ntScriptDef()->name);
}

void oepStyleSheet::oepScriptDef::Name::set(String^ s)
{
	ntScriptDef()->name = Str2Std(s);
	NotifyChanged("Name");
}

String^ oepStyleSheet::oepScriptDef::Code::get()
{
	return Str2Cli(ntScriptDef()->code);
}

void oepStyleSheet::oepScriptDef::Code::set(String^ s)
{
	ntScriptDef()->code = Str2Std(s);
	NotifyChanged("Code");
}

String^ oepStyleSheet::oepScriptDef::Language::get()
{
	return Str2Cli(ntScriptDef()->language);
}

void oepStyleSheet::oepScriptDef::Language::set(String^ s)
{
	ntScriptDef()->language = Str2Std(s);
	NotifyChanged("Language");
}

String^ oepStyleSheet::oepScriptDef::Profile::get()
{
	return Str2Cli(ntScriptDef()->profile);
}

void oepStyleSheet::oepScriptDef::Profile::set(String^ s)
{
	ntScriptDef()->profile = Str2Std(s);
	NotifyChanged("Profile");
}

String^ oepStyleSheet::oepScriptDef::Url::get()
{
	return Str2Cli(ntScriptDef()->uri.value().full());
}

void oepStyleSheet::oepScriptDef::Url::set(String^ s)
{
	ntScriptDef()->uri.mutable_value() = Str2Std(s);
	NotifyChanged("Url");
}

String^ oepStyleSheet::Name::get()
{
	return Str2Cli(ntStyleSheet()->name().value());
}

void oepStyleSheet::Name::set(String^ s)
{
	ntStyleSheet()->name() = Str2Std(s);
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
	res->bind(ntStyleSheet()->getDefaultStyle(),false);
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
	ntStyleSheet()->ClearResourceLibrary();
	for each (oepResourceLibrary^ r in s)
	{
		ntStyleSheet()->addResourceLibrary(r->ntResourceLibrary());
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
	ntStyleSheet()->setScript(_script->ntScriptDef());
	NotifyChanged("Script");
}

void gEarthPack::oepStyleSheet::binded()
{
	_stylemap = gcnew oepStyleMap();
	_stylemap->bind(&(ntStyleSheet()->styles()),false);
	_selectors = gcnew oepStyleSelectorList();
	_selectors->bind(&(ntStyleSheet()->selectors()),false);
	_script = gcnew oepScriptDef();
	_script->bind(ntStyleSheet()->script());
	_resLibs = gcnew oepResourceLibraryMap();
	std::vector<std::string> names = ntStyleSheet()->getResourceNames();
	for (size_t i = 0; i < names.size(); i++)
	{
		oepResourceLibrary^ r = gcnew oepResourceLibrary("","");
		r->bind(ntStyleSheet()->getResourceLibrary(names[i]));
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
					ntStyleSheet()->addResourceLibrary(r->ntResourceLibrary());
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
					ntStyleSheet()->removeResourceLibrary(r->ntResourceLibrary());
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
		ntStyleSheet()->ClearResourceLibrary();
		break;
	}
	default:
		break;
	}
}
