// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#include "IAudioSystem.h"
#include "../Timing/Timestamp.h"
#include "../Ecs/Catalogue.h"

#ifndef NOVELRT_AUDIO_OPENALAUDIOSYSTEM_H
#define NOVELRT_AUDIO_OPENALAUDIOSYSTEM_H

namespace NovelRT::Audio
{
  class OpenALAudioSystem : public IAudioSystem
  {
    public:
      bool isInitialised = false;

      void Update(NovelRT::Timing::Timestamp stamp,
        NovelRT::Ecs::Catalogue catalogue);

  };
}

#endif //NOVELRT_AUDIO_OPENALAUDIOSYSTEM_H
