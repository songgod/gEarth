#pragma once
#include "oepRefObject.h"
#include "oepValMap.h"
#include "oepResource.h"
using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	public ref class oepResourceLibrary :
		public oepRefObject
	{
	public:
		oepResourceLibrary(String^ name, String^ url);

	public:

		virtual property String^ Name
		{
			String^ get() override;
			void set(String^ p) override;
		}

		property String^ Uri
		{
			String^ get();
			void set(String^ p);
		}
		
		property oepResourceCollection^ Resources
		{
			oepResourceCollection^ get();
			void set(oepResourceCollection^ p);
		}

	public:

		virtual void binded() override;
		virtual void unbinded() override;

	internal:

		osgEarth::ResourceLibrary* ntResourceLibrary() { return as<osgEarth::ResourceLibrary>(); }

	private:

		oepResourceCollection^ _resources;
	};

	public ref class oepResourceLibraryMap : public ObservableCollection<oepResourceLibrary^>
	{

	};
}

