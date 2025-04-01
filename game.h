#pragma once

#include "timer.h"
#include "scene.h"
#include "event.h"
#include "display.h"
#include "filesystem.h"
#include "image.h"
#include "text.h"
#include "audio.h"
#include "keyboard.h"
#include "mouse.h"
#include "palette.h"
#include "util.h"

#include "title.h"
#include "worldview.h"
#include "settings.h"
#include "archive.h"

#include "configuration.h"

struct Game
{
    static bool exit;
    static bool redraw;

    static void MainLoop();

    static bool Initialize(char **argv);
    static void Uninitialize();

    static void InputSwitchboard();
    static void LogicSwitchboard();
    static void DrawingSwitchboard();

};
