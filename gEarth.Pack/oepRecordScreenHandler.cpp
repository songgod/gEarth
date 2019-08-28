#include "stdafx.h"
#include "oepRecordScreenHandler.h"
#include "RecordScreenHandler.h"

using namespace msclr::interop;
using namespace gEarthPack;

oepRecordScreenHandler::oepRecordScreenHandler(String^ file, float fps)
{
	_handle->setValue(new RecordScreenHandler(marshal_as<std::string>(file),fps));
}

void oepRecordScreenHandler::Save()
{
	RecordScreenHandler* rsh = asRecordScreenHandler();
	if (rsh)
		rsh->save();
}

void oepRecordScreenHandler::Start()
{
	RecordScreenHandler* rsh = asRecordScreenHandler();
	if (rsh)
		rsh->start();
}

void oepRecordScreenHandler::Stop()
{
	RecordScreenHandler* rsh = asRecordScreenHandler();
	if (rsh)
		rsh->stop();
}

RecordScreenHandler* oepRecordScreenHandler::asRecordScreenHandler()
{
	return dynamic_cast<RecordScreenHandler*>(_handle->getValue());
}
