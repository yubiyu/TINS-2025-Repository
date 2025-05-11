#pragma once

#include "display.h"
#include "tile.h"
#include "util.h"

#include "image.h"
#include "text.h"
#include "palette.h"

#include <string>

struct Dialog
{
    static bool isActive;

    static constexpr float FRAME_X = 0;
    static constexpr float FRAME_Y = Display::NATIVE_HEIGHT - Tile::HEIGHT * 3;
    static constexpr float FRAME_WIDTH = Tile::WIDTH * 10;
    static constexpr float FRAME_HEIGHT = Tile::HEIGHT * 3;

    static constexpr float TEXT_FIELD_X = Tile::WIDTH * 0.5;  // Relative to FRAME_X
    static constexpr float TEXT_FIELD_Y = Tile::HEIGHT * 0.5; // Relative to FRAME_Y
    static constexpr float TEXT_FIELD_WIDTH = Tile::WIDTH * 9;
    static constexpr float TEXT_FIELD_HEIGHT = Tile::HEIGHT * 3;

    static constexpr float TEXT_LINE_HEIGHT = Text::HEIGHT_8 * 1.5;

    static int textXPosition, textYPosition;
    static std::string text;

    static ALLEGRO_BITMAP *textBuffer;
    /*
    Entire text pre-drawn to buffer.
    Content to be revealed by way of two masks:
    -Character-by-character scrolling.
    -Line-by-line scrolling.
    */

    static void Initialize();
    static void Uninitialize();

    static void Logic();
    static void Drawing();
    static void Input();

    static void Activate(std::string text_content);
    static void Deactivate();
};
