#pragma once
#include "oepEventHandler.h"
#include "RecordScreenHandler.h"
namespace gEarthPack
{
	public ref class oepRecordScreenHandler :
		public oepEventHandler
	{
	public:
		oepRecordScreenHandler(String^ file, float fps);

	public:

		void Save();
		void Start();
		void Stop();

	internal:
		RecordScreenHandler* asRecordScreenHandler();
	};
}

