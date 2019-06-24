#pragma once

using namespace System::ComponentModel;
using namespace System;

namespace gEarthPack
{
	public ref class oepObject : INotifyPropertyChanged
	{
	public:
		oepObject();

	public:

		virtual event PropertyChangedEventHandler^ PropertyChanged;

	public:

		void NotifyChanged(String^ property)
		{
			PropertyChanged(this, gcnew PropertyChangedEventArgs(property));
		}
	};
}

