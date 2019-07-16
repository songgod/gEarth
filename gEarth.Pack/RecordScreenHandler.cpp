#include "stdafx.h"
#include "RecordScreenHandler.h"

using namespace gEarthPack;

RecordScreenHandler::RecordScreenHandler(const std::string &filename, float fps) : RecordCameraPathHandler(filename,fps)
{

}


RecordScreenHandler::~RecordScreenHandler()
{
}

bool gEarthPack::RecordScreenHandler::save()
{
	if (_animPath.valid() && !_animPath->empty())
	{
		// In the future this will need to be written continuously, rather
		// than all at once.
		osgDB::ofstream out(_filename.c_str());
		OSG_NOTICE << "Writing camera file: " << _filename << std::endl;
		_animPath->write(out);
		out.close();
		return true;
	}
	return false;
}
