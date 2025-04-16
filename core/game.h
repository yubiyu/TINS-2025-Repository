#pragma once

#include "core/timer.h"
#include "core/event.h"
#include "core/display.h"
#include "core/filesystem.h"
#include "core/util.h"

#include "input/keyboard.h"
#include "input/mouse.h"

#include "resource/image.h"
#include "resource/text.h"
#include "resource/audio.h"
#include "resource/palette.h"

#include "scene/scene.h"
#include "scene/title.h"
#include "scene/worldview.h"
#include "scene/settings.h"
#include "scene/archive.h"

#include "config/configuration.h"

#include "world/area.h"

struct Game
{
    static constexpr const char* STARTING_AREA = "0";

    static bool exit;
    static bool redraw;

    static void MainLoop();

    static bool Initialize(char **argv);
    static void Uninitialize();

    static void InputSwitchboard();
    static void LogicSwitchboard();
    static void DrawingSwitchboard();

};
