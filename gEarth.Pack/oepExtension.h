#pragma once
#include "oepObject.h"
#include "Handle.h"
#include "oepConfigOptions.h"
#include <osgEarth/Extension>
#include <osgEarth/Map>

using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	public ref class oepExtension : oepObject
	{
	public:
		oepExtension();
		~oepExtension();
		!oepExtension();

	public:

		virtual property String^ Name
		{
			String^ get() override;
			void set(String^ v) override;
		}

	internal:

		osgEarth::Extension* asoeExtension();

	protected:

		typedef Handle<osgEarth::Extension> ExtensionHandle;
		ExtensionHandle* _handle;

	};

	public ref class oepExtensions : public ObservableCollection<oepExtension^>
	{
	public:
		oepExtensions() {}
	};
}


