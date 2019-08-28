#pragma once

#include "AnimationPathOptions.h"

namespace osgEarth
{
	namespace AnimationPath
	{
		class AnimationPathExtension :
			public Extension, public AnimationPathOptions
		{
		public:
			META_OE_Extension(osgEarth, AnimationPathExtension, animationpath);

		public:
			AnimationPathExtension();
			AnimationPathExtension(const ConfigOptions& options);

		protected:
			virtual ~AnimationPathExtension();
		};
	}
}


