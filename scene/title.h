#pragma once

#include "core/display.h"
#include "core/util.h"

#include "input/keyboard.h"

#include "resource/image.h"
#include "resource/text.h"
#include "resource/palette.h"

#include "scene/scene.h"
#include "scene/menu.h"

#include <string>
#include <unordered_map>
#include <iostream>

struct Title
{
/// Title text
    static constexpr char const* TITLE_TEXT = "Ericennes";
    static const int TITLE_TEXT_X = Tile::HALF_WIDTH;
    static const int TITLE_TEXT_Y = Tile::HEIGHT*1;

    static constexpr float TITLE_IMAGE_X = 0;
    static constexpr float TITLE_IMAGE_Y = 0;

/// Title options
    enum enumOptions
    {
        OPTION_NEW_GAME = 0,
        OPTION_LOAD_GAME = 1,
        OPTION_ARCHIVE = 2,
        OPTION_SETTINGS = 3,
        OPTION_EXIT = 4
    };
    static const int NUM_OPTIONS = 5;
    static const int FIRST_OPTION = OPTION_NEW_GAME;
    static const int LAST_OPTION = OPTION_EXIT;

    static const inline std::unordered_map<int, std::string> optionStrings =
    {
        {OPTION_NEW_GAME, "New Game"},
        {OPTION_LOAD_GAME, "Load Game"},
        {OPTION_ARCHIVE, "Archive"},
        {OPTION_SETTINGS, "Settings"},
        {OPTION_EXIT, "Exit"}
    };

    static int optionTextX[NUM_OPTIONS];
    static const int OPTION_TEXT_X_BASE = TITLE_TEXT_X;

    static int optionTextY[NUM_OPTIONS];
    static const int OPTION_TEXT_Y_BASE = Tile::HEIGHT*4;
    static const int OPTION_TEXT_Y_SPACING = Tile::HALF_HEIGHT * 1.5;

    static int targetedOption;
    static bool exitOptionSelected;

/// Title functions
    static void Initialize();

    static void Logic();
    static void Input();
    static void Drawing();

    static void AdjustTargetedOptionUp();
    static void AdjustTargetedOptionDown();
    static void SetTargetedOption(int whichOption);
};
