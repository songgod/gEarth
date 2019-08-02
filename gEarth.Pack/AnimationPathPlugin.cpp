#include "Stdafx.h"

#include "AnimationPathExtension.h"

#include <osgDB/ReaderWriter>
#include <osgDB/Registry>
#include <osgDB/FileNameUtils>

namespace osgEarth {
	namespace AnimationPath
	{
		class AnimationPathPlugin : public osgDB::ReaderWriter
		{
		public:

			AnimationPathPlugin() {
				supportsExtension("osgearth_animationpath", "osgEarth Animationpath Extension");
			}

			const char* className() const {
				return "osgEarth Animationpath Extension";
			}

			virtual ~AnimationPathPlugin() { }

			ReadResult readObject(const std::string& filename, const osgDB::Options* dbOptions) const
			{
				if (!acceptsExtension(osgDB::getLowerCaseFileExtension(filename)))
					return ReadResult::FILE_NOT_HANDLED;

				return ReadResult(new AnimationPathExtension(Extension::getConfigOptions(dbOptions)));
			}
		};

		REGISTER_OSGPLUGIN(osgearth_animationpath, AnimationPathPlugin)

	}
}