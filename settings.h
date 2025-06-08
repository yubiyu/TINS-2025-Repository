#pragma once

#include "display.h"
#include "util.h"

#include "keyboard.h"

#include "image.h"
#include "text.h"
#include "audio.h"
#include "palette.h"

#include "scene.h"
#include "menu.h"

#include <unordered_map>
#include <string>
#include <iostream>

#include "configuration.h"

struct Settings
{
    /// Options
    enum enumOptions
    {
        OPTION_FULLSCREEN = 0,
        OPTION_RESOLUTION = 1,
        OPTION_VSYNC = 2,
        OPTION_FPS = 3,
        OPTION_PALETTE = 4,

        OPTION_BGM_LEVEL = 5,
        OPTION_SFX_LEVEL = 6,
        OPTION_RETURN_TO_TITLE = 7
    };
    static const int NUM_OPTIONS = 8;
    static const int FIRST_OPTION = OPTION_FULLSCREEN;
    static const int LAST_OPTION = OPTION_RETURN_TO_TITLE;
    static const int FIRST_DISPLAY_OPTION = OPTION_FULLSCREEN;
    static const int LAST_DISPLAY_OPTION = OPTION_PALETTE;
    static const int FIRST_AUDIO_OPTION = OPTION_BGM_LEVEL;
    static const int LAST_AUDIO_OPTION = OPTION_SFX_LEVEL;

    static const inline std::unordered_map<int, std::string> optionLabels =
        {
            {OPTION_FULLSCREEN, "Display"},
            {OPTION_RESOLUTION, "Scale"},
            {OPTION_VSYNC, "Vsync"},
            {OPTION_FPS, "FPS"},
            {OPTION_PALETTE, "Palette"},

            {OPTION_BGM_LEVEL, "Music"},
            {OPTION_SFX_LEVEL, "Sound"},
            {OPTION_RETURN_TO_TITLE, "Return to Title"},
    };
    static std::unordered_map<int, std::string> optionValues;

    static const int OPTION_LABELS_X = Tile::HALF_WIDTH * 1;
    static const int OPTION_VALUES_X = Tile::HALF_WIDTH * 9;

    static int optionTextY[NUM_OPTIONS];
    static const int OPTION_TEXT_Y_BASE = Tile::HEIGHT * 1;
    static const int OPTION_TEXT_Y_SPACING = Tile::HALF_HEIGHT * 1.5;

    static int targetedOption;

    /// Graphics settings
    static bool fullscreenOption;
    static int windowScaleOption;
    static const int WINDOW_SCALE_MIN = 1;
    static const int WINDOW_SCALE_MAX = 10;
    static std::string windowWidthText;
    static std::string windowHeightText;
    static int vsyncOption;
    static int fpsOption;
    static int paletteOption;

    /// Audio settings
    static int bgmBars;
    static int sfxBars;
    static const int MAX_VOLUME_BARS = 10;
    static constexpr float VOLUME_BARS_X = OPTION_LABELS_X + Tile::WIDTH * 3;
    static constexpr float VOLUME_BAR_WIDTH = Tile::HALF_WIDTH;
    static float bgmBarsTotalWidth;
    static float sfxBarsTotalWidth;
    static constexpr float VOLUME_BAR_HEIGHT = Tile::HALF_HEIGHT;

    /// Cheat settings
    static bool cheatsEnabled;

    /// Settings functions
    static void Initialize();

    static void Logic();
    static void Input();
    static void Drawing();

    static void AdjustTargetedOptionUp();
    static void AdjustTargetedOptionDown();
    static void SetTargetedOption(int whichOption);

    static void UpdateWindowScaleText();

    static void SetFullscreenOption(bool is_fullscreen);
    static void SetWindowScaleOption(int scale);
    static void SetVsyncOption(int vsync_mode);
    static void SetFPSOption(int set_fps);
    static void SetPaletteOption(int set_pal);

    static void SetBgmBarsOption(int bars);
    static void SetSfxBarsOption(int bars);

    static void SetCheatsEnabledOption(int enabled);

    static void SaveToConfig();
    static void LoadFromConfig();
};
