#pragma once
#include "oepValObject.h"
#include "oepValList.h"

using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	ref class oepConfig;
	public ref class oepConfigSet : public oepValList<oepConfig,osgEarth::Config>
	{

	};

	public ref class oepConfig :
		public oepValObject<osgEarth::Config>
	{
	public:
		oepConfig();

	public:

		property String^ Referrer
		{
			String^ get();
			void set(String^ p);
		}

		property bool IsLocation
		{
			bool get();
			void set(bool p);
		}

		property String^ ExternalRef
		{
			String^ get();
			void set(String^ p);
		}

		property String^ Joson
		{
			String^ get();
			void set(String^ p);
		}

		property bool IsEmpty
		{
			bool get();
		}

		property bool IsSimple
		{
			bool get();
		}

		property String^ Key
		{
			String^ get();
			void set(String^ p);
		}

		property String^ Value
		{
			String^ get();
		}

		property oepConfigSet^ Children
		{
			oepConfigSet^ get();
			void set(oepConfigSet^ p);
		}

	internal:

		virtual void binded() override;
		virtual void unbinded() override;

	private:

		oepConfigSet^ _children;
	};


}

