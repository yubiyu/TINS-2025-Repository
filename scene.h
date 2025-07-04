#pragma once

#include "audio.h"

struct Scene
{
    enum enumScene
    {
        SCENE_TITLE,

        SCENE_WORLDVIEW,
        SCENE_GAME_RESULT,

        SCENE_LOADGAME,
        SCENE_ARCHIVE,
        SCENE_SETTINGS,
    };
    static int scene;

    enum enumInputContext
    {
        INPUT_CONTEXT_TITLE,

        INPUT_CONTEXT_WORLDVIEW,

        INPUT_CONTEXT_GAME_RESULT,

        INPUT_CONTEXT_LOADGAME,
        INPUT_CONTEXT_ARCHIVE,
        INPUT_CONTEXT_SETTINGS,
    };
    static int inputContext;

    static void Initialize();
    static void ChangeScene(int whichScene);
    static void ChangeInputContext(int whichContext);
};
