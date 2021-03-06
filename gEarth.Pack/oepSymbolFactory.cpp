#include "stdafx.h"
#include "oepSymbolFactory.h"
#include "oepUnkownSymbol.h"
#include "oepAltitudeSymbol.h"

using namespace gEarthPack;
using namespace osgEarth::Symbology;

namespace gEarthPack
{
	private ref class oepUnkownSymbolCreator : IoepSymbolCreator
	{
	public:
		virtual String^ supportType()
		{
			return "unknown";
		}
		virtual oepSymbol ^ createSymbol(IntPtr param)
		{
			Symbol* pSymbol = (Symbol*)param.ToPointer();
			oepUnkownSymbol^ res = gcnew oepUnkownSymbol();
			res->bind(pSymbol);
			return res;
		}
	};

	private ref class oepAltitudeSymbolCreator : IoepSymbolCreator
	{
	public:
		virtual String^ supportType()
		{
			return "altitude";
		}
		virtual oepSymbol ^ createSymbol(IntPtr param)
		{
			AltitudeSymbol* pSymbol = (AltitudeSymbol*)param.ToPointer();
			oepAltitudeSymbol^ res = gcnew oepAltitudeSymbol();
			res->bind(pSymbol);
			return res;
		}
	};
}

static oepSymbolFactory::oepSymbolFactory()
{
	_symbolcreatorcache = gcnew Dictionary<String^, IoepSymbolCreator^>();
	registerCreator(gcnew oepUnkownSymbolCreator());
	registerCreator(gcnew oepAltitudeSymbolCreator());
}

void oepSymbolFactory::registerCreator(IoepSymbolCreator^ creator)
{
	if (creator == nullptr)
		return;
	_symbolcreatorcache[creator->supportType()] = creator;
}

void oepSymbolFactory::unregisterCreator(String^ type)
{
	_symbolcreatorcache->Remove(type);
}

oepSymbol^ oepSymbolFactory::creatorSymbol(String^ type, IntPtr param)
{
	if (_symbolcreatorcache->ContainsKey(type))
		return _symbolcreatorcache[type]->createSymbol(param);

	return _symbolcreatorcache["unknown"]->createSymbol(param);
}
