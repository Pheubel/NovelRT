// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#include "IAudioSystem.h"
#include "../Timing/Timestamp.h"
#include "../Ecs/Catalogue.h"

#ifndef NOVELRT_AUDIO_NULLAUDIOSYSTEM_H
#define NOVELRT_AUDIO_NULLAUDIOSYSTEM_H

namespace NovelRT::Audio
{
  class NullAudioSystem : public IAudioSystem
  {
    public:
      NullAudioSystem();
      void Update(NovelRT::Timing::Timestamp stamp,
        NovelRT::Ecs::Catalogue catalogue);

    private:
      bool Initialize();
  };
}

#endif //NOVELRT_AUDIO_NULLAUDIOSYSTEM_H
