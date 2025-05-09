#pragma once

#include "resource/audio.h"

struct Scene
{
    enum enumScene
    {
        SCENE_TITLE,

        SCENE_WORLDVIEW,

        SCENE_ARCHIVE,
        SCENE_SETTINGS,
    };
    static int scene;

    enum enumInputContext
    {
        INPUT_CONTEXT_TITLE,

        INPUT_CONTEXT_WORLDVIEW,

        INPUT_CONTEXT_ARCHIVE,
        INPUT_CONTEXT_SETTINGS,
    };
    static int inputContext;

    static void Initialize();
    static void ChangeScene(int whichScene);
    static void ChangeInputContext(int whichContext);
};
