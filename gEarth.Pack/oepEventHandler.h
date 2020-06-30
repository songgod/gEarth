#pragma once
#include "oepRefObject.h"

using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	public ref class oepEventHandler :
		public oepRefObject<osgGA::EventHandler>
	{
	public:
		oepEventHandler();

	public:

		virtual property String^ Name
		{
			String^ get() override;
			void set(String^ v) override;
		}

		property bool Keep
		{
			bool get();
			void set(bool v);
		}

	internal:

		virtual void bind(osgEarth::MapNode* pMapNode){}
		virtual void unbind(osgEarth::MapNode* pMapNode){}

	private:

		bool _keep;

	};

	public ref class oepEventHandlers : public ObservableCollection<oepEventHandler^>
	{
	public:
		oepEventHandlers() {}
	};
}
