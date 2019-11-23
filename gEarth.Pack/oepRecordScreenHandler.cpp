#include "stdafx.h"
#include "oepRecordScreenHandler.h"
#include "RecordScreenHandler.h"

using namespace msclr::interop;
using namespace gEarthPack;

oepRecordScreenHandler::oepRecordScreenHandler(String^ file, float fps)
{
	setRef(new RecordScreenHandler(marshal_as<std::string>(file),fps));
}

void oepRecordScreenHandler::Save()
{
	RecordScreenHandler* rsh = as<RecordScreenHandler>();
	if (rsh)
		rsh->save();
}

void oepRecordScreenHandler::Start()
{
	RecordScreenHandler* rsh = as<RecordScreenHandler>();
	if (rsh)
		rsh->start();
}

void oepRecordScreenHandler::Stop()
{
	RecordScreenHandler* rsh = as<RecordScreenHandler>();
	if (rsh)
		rsh->stop();
}
