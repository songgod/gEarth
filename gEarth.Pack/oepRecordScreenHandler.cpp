#include "stdafx.h"
#include "oepRecordScreenHandler.h"
#include <msclr\marshal_cppstd.h>  

using namespace msclr::interop;

gEarthPack::oepRecordScreenHandler::oepRecordScreenHandler(String^ file, float fps)
{
	_handle->setValue(new RecordScreenHandler(marshal_as<std::string>(file),fps));
}

void gEarthPack::oepRecordScreenHandler::Save()
{
	gEarthPack::RecordScreenHandler* rsh = asRecordScreenHandler();
	if (rsh)
		rsh->save();
}

void gEarthPack::oepRecordScreenHandler::Start()
{
	gEarthPack::RecordScreenHandler* rsh = asRecordScreenHandler();
	if (rsh)
		rsh->start();
}

void gEarthPack::oepRecordScreenHandler::Stop()
{
	gEarthPack::RecordScreenHandler* rsh = asRecordScreenHandler();
	if (rsh)
		rsh->stop();
}

gEarthPack::RecordScreenHandler* gEarthPack::oepRecordScreenHandler::asRecordScreenHandler()
{
	return dynamic_cast<gEarthPack::RecordScreenHandler*>(_handle->getValue());
}
