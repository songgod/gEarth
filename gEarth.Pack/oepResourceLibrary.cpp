#include "stdafx.h"
#include "oepResourceLibrary.h"

using namespace gEarthPack;
using namespace osgEarth::Symbology;


oepResourceLibrary::oepResourceLibrary(String^ name, String^ url)
{
	bind(new ResourceLibrary(Str2Std(name), osgEarth::URI(Str2Std(url))));
}

String^ oepResourceLibrary::Name::get()
{
	return Str2Cli(ntResourceLibrary()->getName());
}

void oepResourceLibrary::Name::set(String^ p)
{
	ntResourceLibrary()->setName(Str2Std(p));
	NotifyChanged("Name");
}

String^ oepResourceLibrary::Uri::get()
{
	return Str2Cli(ntResourceLibrary()->uri().value().full());
}

void oepResourceLibrary::Uri::set(String^ p)
{
	ntResourceLibrary()->uri() = (Str2Std(p));
	NotifyChanged("Uri");
}

oepResourceCollection^ oepResourceLibrary::Resources::get()
{
	return _resources;
}

void oepResourceLibrary::Resources::set(oepResourceCollection^ p)
{
	_resources = p;
	NotifyChanged("Resources");
}

void oepResourceLibrary::binded()
{
	_resources = gcnew oepResourceCollection();
	/*for (int i = 0; i < ref()->symbols().size(); i++)
	{
		Symbol* pSymbol = val()->symbols()[i];
		String^ type = Str2Cli(pSymbol->getConfig().key());
		oepSymbol^ symbol = oepSymbolFactory::creatorSymbol(type, IntPtr(pSymbol));
		_symbols->Add(symbol);
	}
	_symbols->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &oepStyle::OnMTCollectionChanged);*/
}

void oepResourceLibrary::unbinded()
{
	for each (oepResource^ s in _resources)
	{
		s->unbind();
	}
}
