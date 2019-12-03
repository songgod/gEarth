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

		property bool IsNumber
		{
			bool get();
		}

		property String^ Key
		{
			String^ get();
			void set(String^ p);
		}

		property String^ StrValue
		{
			String^ get();
			void set(String^ p);
		}

		property bool BoolValue
		{
			bool get();
			void set(bool p);
		}
		
		property short ShortValue
		{
			short get();
			void set(short p);
		}

		property unsigned short UshortValue
		{
			unsigned short get();
			void set(unsigned short p);
		}

		property int IntValue
		{
			int get();
			void set(int p);
		}

		property unsigned int UintValue
		{
			unsigned int get();
			void set(unsigned int p);
		}

		property long LongValue
		{
			long get();
			void set(long p);
		}

		property unsigned long UlongValue
		{
			unsigned long get();
			void set(unsigned long p);
		}

		property float FloatValue
		{
			float get();
			void set(float p);
		}

		property double DoubleValue
		{
			double get();
			void set(double p);
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

