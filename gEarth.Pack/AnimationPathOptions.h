#pragma once

#include <osgEarth/Config>
#include <osg/AnimationPath>
#include <osgDB/FileNameUtils>
#include <osgDB/FileUtils>

namespace osgEarth
{
	namespace AnimationPath
	{
		class AnimationPathInfo : public osg::Referenced
		{
		public:

			AnimationPathInfo(){}
			AnimationPathInfo(const std::string& name, const std::string& url):_name(name),_url(url)
			{

			}

		public:

			std::string& name() { return _name; }
			const std::string& name() const { return _name; }
			
			std::string& url() { return _url; }
			const std::string& url() const { return _url; }

			osg::AnimationPath* animationpath() { return path(); }
			const osg::AnimationPath* animationpath() const { return path(); }

		protected:

			osg::AnimationPath* path() const
			{
				if (_anipth.valid())
					return _anipth.get();
				
				_anipth = new osg::AnimationPath();
				if (!_url.empty())
				{
					if (osgDB::fileExists(_url))
					{
						std::ifstream ifs(_url);
						_anipth->read(ifs);
						return _anipth.get();
					}
				}
				return _anipth;
			}

		private:
			std::string _name;
			std::string _url;
			mutable osg::ref_ptr<osg::AnimationPath> _anipth;
		};

		typedef std::vector<osg::ref_ptr<AnimationPathInfo>> AnimationPathInfos;

		class AnimationPathOptions : public osgEarth::DriverConfigOptions
		{
		public:
			AnimationPathOptions(const ConfigOptions& options = ConfigOptions()) :
				DriverConfigOptions(options)
			{
				setDriver("animationpath");
				fromConfig(_conf);
			}
			virtual ~AnimationPathOptions(){}

		public:

			AnimationPathInfos& animationpaths() { return _animationpaths; }
			const AnimationPathInfos& animationpaths() const { return _animationpaths; }

		public:

			Config getConfig() const
			{
				Config conf = DriverConfigOptions::getConfig();
				conf.key() = "animationpath";
				ConfigSet& children = conf.children();
				for (size_t i = 0; i < _animationpaths.size(); i++)
				{
					Config c;
					c.key() = "path";
					c.set("name",_animationpaths[i]->name());
					c.set("url", _animationpaths[i]->url());
					children.push_back(c);
				}
				return conf;
			}

		protected:
			void mergeConfig(const Config& conf) {
				DriverConfigOptions::mergeConfig(conf);
				fromConfig(conf);
			}

		private:
			void fromConfig(const Config& conf) {
				const ConfigSet& children = conf.children("path");
				if (children.size() > 0)
				{
					for (ConfigSet::const_iterator i = children.begin(); i != children.end(); ++i)
					{
						const Config& c = *i;
						std::string name; c.get("name", name);
						std::string url; c.get("url", url);
						_animationpaths.push_back(new AnimationPathInfo(name,url));
					}
				}
			}

		private:

			AnimationPathInfos _animationpaths;
		};
	}
}

