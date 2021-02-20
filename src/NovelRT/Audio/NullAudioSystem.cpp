// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#include <NovelRT/Audio/NullAudioSystem.h>
#include <iostream>
#include <NovelRT/Audio/AudioSoundComponent.h>

namespace NovelRT::Audio
{
  NullAudioSystem::NullAudioSystem()
  {
    isInitialised = Initialize();
  }

  bool NullAudioSystem::Initialize()
  {
    //TODO: Make this use NovelRT logging
    std::cout << "Null Audio System initialised\n" << "Please don't expect any actual sound :D" << std::endl;
    return true;
  }

  void NullAudioSystem::Update(NovelRT::Ecs::Catalogue catalogue)
  {
    auto[audioComponents] = catalogue.GetComponentViews<AudioSoundComponent>();

    for(auto[entity, component] : audioComponents)
    {
      std::cout << "Entity " << entity << "owns AudioSoundComponent " << component.id << std::endl;
    }
  }


} // namespace NovelRT::Ecs
