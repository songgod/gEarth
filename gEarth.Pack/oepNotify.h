#pragma once
using namespace System::ComponentModel;
using namespace System;

namespace gEarthPack
{
	public ref class oepNotify : INotifyPropertyChanged
	{
	public:
		oepNotify();

	public:

		virtual event PropertyChangedEventHandler^ PropertyChanged;

	public:

		void NotifyChanged(String^ property)
		{
			PropertyChanged(this, gcnew PropertyChangedEventArgs(property));
		}
	};
}
