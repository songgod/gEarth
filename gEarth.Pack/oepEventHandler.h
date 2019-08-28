#pragma once
#include "oepRefObject.h"
#include "oepHandle.h"

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

	internal:

		virtual void bind(osgEarth::MapNode* pMapNode){}
		virtual void unbind(osgEarth::MapNode* pMapNode){}
	};

	public ref class oepEventHandlers : public ObservableCollection<oepEventHandler^>
	{
	public:
		oepEventHandlers() {}
	};
}
