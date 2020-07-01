#pragma once
#include "oepRefObject.h"

using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	public ref class oepResource :
		public oepRefObject
	{
	public:
		oepResource();

	public:

		virtual property String^ Name
		{
			String^ get() override;
			void set(String^ p) override;
		}

		property ObservableCollection<String^>^ Tags
		{
			ObservableCollection<String^>^ get();
			void set(ObservableCollection<String^>^ p);
		}

	public:

		virtual void binded() override;
		virtual void unbinded() override;

	internal:

		osgEarth::Resource* ntResource() { return as<osgEarth::Resource>(); }
	protected:

		void OnMTCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e);

	private:

		ObservableCollection<String^>^ _tags;
	};

	public ref class oepResourceCollection : ObservableCollection<oepResource^>
	{

	};
}

