// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#include <stdint.h>

#ifndef NOVELRT_AUDIO_AUDIOSOUNDCOMPONENT_H
#define NOVELRT_AUDIO_AUDIOSOUNDCOMPONENT_H

namespace NovelRT::Audio
{
  struct AudioSoundComponent
  {
    public:
      uintptr_t id;
      float volume;
      float pitch;
  };
}

#endif //NOVELRT_AUDIO_AUDIOSOUNDCOMPONENT_H
