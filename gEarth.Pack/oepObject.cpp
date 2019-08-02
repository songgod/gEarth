#include "stdafx.h"
#include "oepObject.h"

using namespace gEarthPack;

oepObject::oepObject()
{
}

String^ oepObject::Name::get()
{
	throw gcnew System::NotImplementedException();
}

void oepObject::Name::set(String^ v)
{
	throw gcnew System::NotImplementedException();
}
