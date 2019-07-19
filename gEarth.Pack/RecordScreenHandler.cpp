#include "stdafx.h"
#include "RecordScreenHandler.h"
#include <sstream>
#include <osgDB/FileUtils>
#include <osgDB/FileNameUtils>
#include <iomanip>

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

void gEarthPack::RecordScreenHandler::start()
{
	_currentlyRecording = true;
	_animStartTime = osg::Timer::instance()->tick();
	_animPath = new osg::AnimationPath();

	if (!_filename.empty())
	{
		std::stringstream ss;
		ss << osgDB::getNameLessExtension(_filename);
		if (_autoinc != -1)
		{
			ss << "_" << std::setfill('0') << std::setw(2) << _autoinc;
			_autoinc++;
		}
		ss << "." << osgDB::getFileExtension(_filename);

		OSG_NOTICE << "Recording camera path to file " << ss.str() << std::endl;
		_fout.open(ss.str().c_str());

		// make sure doubles are not trucated by default stream precision = 6
		_fout.precision(15);
	}
	else
	{
		OSG_NOTICE << "Recording camera path." << std::endl;
	}
}

void gEarthPack::RecordScreenHandler::stop()
{
	_currentlyRecording = false;
	_delta = 0.0f;

	if (_fout) _fout.close();
}
