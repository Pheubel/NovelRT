// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_INK_STORY_H
#define NOVELRT_INTEROP_INK_STORY_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtBool Nrt_Story_canContinue(NrtStoryHandle story);
    void Nrt_Story_chooseChoiceIndex(NrtStoryHandle story, int32_t choiceIdx);
    const char* Nrt_Story_continue(NrtStoryHandle story);
    const char* Nrt_Story_continueMaximally(NrtStoryHandle story);
    void Nrt_Story_resetState(NrtStoryHandle story);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_INK_STORY_H
