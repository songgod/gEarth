#pragma once
#include "oepObject.h"
#include "Handle.h"
#include <osgGA/EventHandler>
#include <osgEarth/MapNode>

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
		virtual void setMapNode(osgEarth::MapNode* pMapNode){}
		virtual osgEarth::MapNode* getMapNode() { return NULL; }
		virtual void quit(){}

	protected:

		typedef Handle<osgGA::EventHandler> EventHandlerHandle;
		EventHandlerHandle* _handle;
	};

	public ref class oepEventHandlers : public ObservableCollection<oepEventHandler^>
	{
	public:
		oepEventHandlers() {}
	};
}
