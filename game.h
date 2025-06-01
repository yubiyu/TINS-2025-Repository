#pragma once

#include "timer.h"
#include "event.h"
#include "display.h"
#include "filesystem.h"
#include "util.h"

#include "keyboard.h"
#include "mouse.h"

#include "image.h"
#include "text.h"
#include "audio.h"
#include "palette.h"

#include "scene.h"
#include "title.h"
#include "worldview.h"
#include "loadgame.h"
#include "settings.h"
#include "archive.h"

#include "configuration.h"

#include "area.h"
#include "actor.h"
#include "pc.h"

#include <iostream>

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
