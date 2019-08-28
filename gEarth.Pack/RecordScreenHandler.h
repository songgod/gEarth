#pragma once

namespace gEarthPack
{
	class RecordScreenHandler :
		public osgViewer::RecordCameraPathHandler
	{
	public:
		RecordScreenHandler(const std::string &filename = "saved_animation.path", float fps = 25.0f);
		~RecordScreenHandler();

	public:

		bool save();
		void start();
		void stop();
	};
}
