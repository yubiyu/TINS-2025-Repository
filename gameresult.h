#pragma once

#include "display.h"
#include "keyboard.h"

#include "tile.h"
#include "util.h"

#include "image.h"
#include "text.h"
#include "palette.h"

#include "pc.h"
#include "area.h"

#include "scene.h"

#include <string>
#include <algorithm>

struct GameResult
{
    static bool isActive;    // The frame appears. Logic() progresses each tick.
    static bool isScrolling; // textFieldRevealedRow/textFieldRevealedCol progresses each tick.

    /*
        Some distinctions:
    Frame      = The green rectangular sprite that encompasses the text field.
    Text Field = The area intended for the three rows of text to be drawn within the frame.
    Text area/text buffer  = The entire text, to be drawn as a rectangular area. Can easily extend far below the text field - and above, as scrolling proceeds.
    */

    static std::string text;
    static ALLEGRO_BITMAP *textBuffer;
    static int textBufferXPosition, textBufferYPosition; // sx/sy for al_draw_bitmap_region
    /*
    Entire text pre-drawn to buffer.
    Content to be revealed by way of two masks:
    -Character-by-character scrolling.
    -Line-by-line scrolling.
    */

    static constexpr float FRAME_X = 0;
    static constexpr float FRAME_Y = 0;
    static constexpr float FRAME_WIDTH = Tile::WIDTH * 10;
    static constexpr float FRAME_HEIGHT = Tile::HEIGHT * 9;

    static constexpr float TEXT_FIELD_X = FRAME_X + Tile::HALF_WIDTH;
    static constexpr float TEXT_FIELD_Y = FRAME_Y + Tile::HALF_HEIGHT;
    static constexpr float TEXT_FIELD_WIDTH = FRAME_WIDTH - Tile::WIDTH;
    static constexpr float TEXT_FIELD_HEIGHT = FRAME_HEIGHT - Tile::HEIGHT;

    static constexpr int TEXT_FIELD_ROWS = 10; // 3 rows for 3 lines. Note that lines are numbered 0 to 2.
    static const int TEXT_FIELD_COLS = 18;    // 18 cols for 18 characters. Note that cols are numbered 0 to 17.

    static constexpr float TEXT_FIELD_ROW_HEIGHT = Text::HEIGHT_8 * 1.5;
    static const int TEXT_CHAR_WIDTH = 8; // Assumes monospace, for now.

    static int textFieldTopRow; // The top-most row within the text field.
    static int textBufferNumRows;
    static std::vector<int> textBufferRowWidths;

    static int textFieldRevealedRow; // Previously known as "caretRow" or "scrollingRow".
    static int textFieldRevealedCol; // Only applies to current row.

    static const int FRAME_SCROLLING_TICKS_NEEDED = 3;
    static int frameScrollingTick; // Delay for text-scrolling.

    static const int TEXT_BUFFER_ADVANCE_ROWS = 0;

    static bool spaceAtCaret;
    static int caretFrame; // Text scrolling caret alternates between "0 = black" and "1 = white."

    static void Initialize();
    static void Uninitialize();

    static void Logic();
    static void Drawing();
    static void Input();

    static void Activate(std::string text_content);
    //static void Activate(const char *section, const char *key);
    //static void Activate(const char *section, const char *key, std::string appendText);
    static void ActivateEnding();
    static void Deactivate();
    static void Advance();
};