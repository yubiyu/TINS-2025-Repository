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

    /*
        Some distinctions:
    Frame      = The green rectangular sprite that encompasses the text field.
    Text Field = The area intended for the three rows of text to be drawn within the frame.
    Text area  = The entire text, to be drawn as a rectangular area. Can easily extend far below the text field - and above, as scrolling proceeds. 
    */

    static constexpr float FRAME_X = 0;
    static constexpr float FRAME_Y = Display::NATIVE_HEIGHT - Tile::HEIGHT * 3;
    static constexpr float FRAME_WIDTH = Tile::WIDTH * 10;

    static constexpr float TEXT_FIELD_X = FRAME_X + Tile::WIDTH * 0.5;
    static constexpr float TEXT_FIELD_Y = FRAME_Y + Tile::HEIGHT * 0.5;
    static constexpr float TEXT_FIELD_WIDTH = FRAME_WIDTH - Tile::WIDTH;

    static constexpr float TEXT_FIELD_ROW_HEIGHT = Text::HEIGHT_8 * 1.5;

    static int textXPosition, textYPosition;
    static std::string text;

    static ALLEGRO_BITMAP *textFieldBuffer;
    /*
    Entire text pre-drawn to buffer.
    Content to be revealed by way of two masks:
    -Character-by-character scrolling.
    -Line-by-line scrolling.
    */

    static const int TEXT_FIELD_ROWS = 3;  // 3 rows for 3 lines.
    static const int TEXT_FIELD_COLS = 18; // 18 cols for 18 characters.

    static int currentTextRow; // The bottom-most row revealed.
    static int currentTextCol; // The right-most character revealed on the current row.
    static int textNumRows;

    static int frameScrollingTick; // Delay for text-scrolling
    static const int FRAME_SCROLLING_TICKS_NEEDED = 3;
    static int caretFrame; // Text scrolling caret alternates between "0 = black" and "1 = white."

    static void Initialize();
    static void Uninitialize();

    static void Logic();
    static void Drawing();
    static void Input();

    static void Activate(std::string text_content);
    static void Deactivate();

};
