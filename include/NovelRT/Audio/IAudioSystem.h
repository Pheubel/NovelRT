// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#include "../Timing/Timestamp.h"
#include "../Ecs/Catalogue.h"


#ifndef NOVELRT_AUDIO_IAUDIOSYSTEM_H
#define NOVELRT_AUDIO_IAUDIOSYSTEM_H

namespace NovelRT::Audio
{
  class IAudioSystem
  {
    public:
      virtual void Update(NovelRT::Timing::Timestamp stamp,
        NovelRT::Ecs::Catalogue catalogue) = 0;
      bool isInitialised = false;
  };
}

#endif //NOVELRT_AUDIO_IAUDIOSYSTEM_H
