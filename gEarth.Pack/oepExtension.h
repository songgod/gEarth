#pragma once
#include "oepRefObject.h"
#include "oepConfigOptions.h"

using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	public ref class oepExtension : oepRefObject
	{
	public:
		oepExtension();

	public:

		virtual property String^ Name
		{
			String^ get() override;
			void set(String^ v) override;
		}
	};

	public ref class oepExtensions : public ObservableCollection<oepExtension^>
	{
	public:
		oepExtensions() {}
	};
}


