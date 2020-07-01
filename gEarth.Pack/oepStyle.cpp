#include "stdafx.h"
#include "oepStyle.h"
#include "oepSymbolFactory.h"

using namespace gEarthPack;
using namespace osgEarth::Symbology;


oepStyle::oepStyle()
{
	bind(new Style(), true);
}

oepStyle^ oepStyle::combineWith(oepStyle^ style)
{
	Style* pstyle = new Style();
	*pstyle = val()->combineWith(*(style->val()));
	oepStyle^ res = gcnew oepStyle();
	res->bind(pstyle, true);
	return res;
}

void oepStyle::binded()
{
	_symbols = gcnew oepSymbolCollection();
	for (int i = 0; i < val()->symbols().size(); i++)
	{
		Symbol* pSymbol = val()->symbols()[i];
		String^ type = Str2Cli(pSymbol->getConfig().key());
		oepSymbol^ symbol = oepSymbolFactory::creatorSymbol(type, IntPtr(pSymbol));
		_symbols->Add(symbol);
	}
	_symbols->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepStyle::OnMTCollectionChanged);
}

void oepStyle::unbinded()
{
	for each (oepSymbol^ s in _symbols)
	{
		s->unbind();
	}
}

void oepStyle::OnMTCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e)
{
	switch (e->Action)
	{
	case System::Collections::Specialized::NotifyCollectionChangedAction::Add:
	{
		if (e->NewItems != nullptr && e->NewItems->Count > 0)
		{
			for (int i = 0; i < e->NewItems->Count; i++)
			{
				oepSymbol^ symbol = dynamic_cast<oepSymbol^>(e->NewItems[i]);
				if (symbol != nullptr)
				{
					val()->addSymbol(symbol->ntSymbol());
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
				oepSymbol^ symbol = dynamic_cast<oepSymbol^>(e->OldItems[i]);
				if (symbol != nullptr)
				{
					val()->removeSymbol(symbol->ntSymbol());
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
		val()->symbols().clear();
		break;
	}
	default:
		break;
	}
}



String^ oepStyle::Name::get()
{
	return Str2Cli(val()->getName());
}

void oepStyle::Name::set(String^ p)
{
	val()->setName(Str2Std(p));
	NotifyChanged("Name");
}

bool oepStyle::IsEmpty::get()
{
	return val()->empty();
}

oepSymbolCollection^ oepStyle::Symbols::get()
{
	return _symbols;
}

void oepStyle::Symbols::set(oepSymbolCollection^ p)
{
	_symbols = p;
	SymbolList lst;
	for each (oepSymbol^ s in p)
	{
		lst.push_back(s->ntSymbol());
	}
	val()->symbols() = lst;
	NotifyChanged("Symbols");
}
