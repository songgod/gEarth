#include "stdafx.h"
#include "oepResourceLibrary.h"

using namespace gEarthPack;
using namespace osgEarth::Symbology;
using namespace msclr::interop;

oepResourceLibrary::oepResourceLibrary(String^ name, String^ url)
{
	bind(new ResourceLibrary(marshal_as<std::string>(name), osgEarth::URI(marshal_as<std::string>(url))));
}

String^ oepResourceLibrary::Name::get()
{
	return marshal_as<String^>(ref()->getName());
}

void oepResourceLibrary::Name::set(String^ p)
{
	ref()->setName(marshal_as<std::string>(p));
	NotifyChanged("Name");
}

String^ oepResourceLibrary::Uri::get()
{
	return marshal_as<String^>(ref()->uri().mutable_value().full());
}

void oepResourceLibrary::Uri::set(String^ p)
{
	ref()->uri() = (marshal_as<std::string>(p));
	NotifyChanged("Uri");
}

oepResourceCollection^ oepResourceLibrary::Resources::get()
{
	return _resources;
}

void oepResourceLibrary::Resources::set(oepResourceCollection^ p)
{
	_resources = p;

}

void oepResourceLibrary::binded()
{
	_resources = gcnew oepResourceCollection();
	/*for (int i = 0; i < ref()->symbols().size(); i++)
	{
		Symbol* pSymbol = val()->symbols()[i];
		String^ type = marshal_as<String^>(pSymbol->getConfig().key());
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
