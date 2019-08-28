#pragma once
#include "oepObject.h"
#include "oepHandle.h"

using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	public ref class oepEventHandler :
		public oepObject
	{
	public:
		oepEventHandler();
		~oepEventHandler();
		!oepEventHandler();

	public:

		virtual property String^ Name
		{
			String^ get() override;
			void set(String^ v) override;
		}

	internal:

		osgGA::EventHandler* asosgEventHandler();
		virtual void bind(osgEarth::MapNode* pMapNode){}
		virtual void unbind(osgEarth::MapNode* pMapNode){}

	protected:

		typedef oepHandle<osgGA::EventHandler> EventHandlerHandle;
		EventHandlerHandle* _handle;
	};

	public ref class oepEventHandlers : public ObservableCollection<oepEventHandler^>
	{
	public:
		oepEventHandlers() {}
	};
}
