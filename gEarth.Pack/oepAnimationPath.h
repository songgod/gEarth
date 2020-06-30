#pragma once
#include "oepValObject.h"
#include "oepRefObject.h"
#include "oepRender.h"
#include "AnimationPathExtension.h"

using namespace System::Collections::ObjectModel;

namespace gEarthPack
{
	public ref class oepControlPoint : 
		public oepValObject<osg::AnimationPath::ControlPoint>
	{
	public:
		oepControlPoint();

	public:

		property double Time
		{
			double get();
			void set(double v);
		}

	public:

		static oepControlPoint^ MakeControlPoint(oepRender^ render, double time);

	internal:

		oepControlPoint(osg::AnimationPath::ControlPoint& cp);

	private:

		double _time;
	};

	public ref class oepControlPoints : public ObservableCollection<oepControlPoint^>
	{

	};

	public ref class oepAnimationPath :
		public oepRefObject<osgEarth::AnimationPath::AnimationPathInfo>
	{
	public:
		oepAnimationPath();

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

		static void PlayPath(oepAnimationPath^ path, oepRender^ render);
		static oepAnimationPath^ From(String^ url);

	public:

		bool Save();

	internal:

		oepAnimationPath(osgEarth::AnimationPath::AnimationPathInfo* info);

	private:

		void init();
		void OnControlPointsCollectionChanged(System::Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e);

	protected:

		oepControlPoints^ _controlpoints;
	};

	public ref class oepAnimationPaths : public ObservableCollection<oepAnimationPath^>
	{

	};
}
