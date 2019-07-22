#pragma once
#include "oepObject.h"
#include "Handle.h"
#include "Render.h"
#include "AnimationPathOptions.h"
#include <osg/AnimationPath>

using namespace osgEarth::AnimationPath;
using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	public ref class oepControlPoint : 
		public oepNotify
	{
	public:
		oepControlPoint();
		~oepControlPoint();
		!oepControlPoint();

	public:

		property double Time
		{
			double get();
			void set(double v);
		}

	public:

		static oepControlPoint^ MakeControlPoint(Render^ render, double time);

	internal:

		oepControlPoint(const osg::AnimationPath::ControlPoint& cp);
		void setHandle(osg::AnimationPath::ControlPoint* cp);
		void resetHandle();
		osg::AnimationPath::ControlPoint* asosgControlPoint();

	private:

		osg::AnimationPath::ControlPoint* _handle;
		double _time;
		bool _ownhandle;
	};

	public ref class oepControlPoints : public ObservableCollection<oepControlPoint^>
	{

	};

	public ref class oepAnimationPath :
		public oepObject
	{
	public:
		oepAnimationPath();
		!oepAnimationPath();
		~oepAnimationPath();

	public:

		virtual property String^ Name
		{
			String^ get() override;
			void set(String^ v) override;
		}

		property String^ Url
		{
			String^ get();
			void set(String^ v);
		}

		property oepControlPoints^ ControlPoints
		{
			oepControlPoints^ get();
		}

	public:

		static void PlayPath(oepAnimationPath^ path, Render^ render);
		static oepAnimationPath^ From(String^ url);

	public:

		bool Save();

	internal:

		oepAnimationPath(AnimationPathInfo* info);
		AnimationPathInfo* asoeAnimationPathInfo();

	private:

		void init();
		void OnControlPointsCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e);

	protected:

		typedef Handle<AnimationPathInfo> AnimationPathInfoHandle;
		AnimationPathInfoHandle* _handle;
		oepControlPoints^ _controlpoints;
	};

	public ref class oepAnimationPaths : public ObservableCollection<oepAnimationPath^>
	{

	};
}
