// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.
#include <NovelRT/Audio/NullAudioSystem.h>
#include <iostream>

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

  void NullAudioSystem::Update(NovelRT::Timing::Timestamp stamp, NovelRT::Ecs::Catalogue catalogue)
  {

  }


} // namespace NovelRT::Ecs
