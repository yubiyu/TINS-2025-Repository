#include "dialog.h"

bool Dialog::isActive {};

std::string Dialog::text {};
ALLEGRO_BITMAP *Dialog::textBuffer {};
int Dialog::textBufferXPosition {}, Dialog::textBufferYPosition {};

int Dialog::textRow {};
int Dialog::textCol {};
int Dialog::textNumRows {};
int Dialog::frameScrollingTick {};

int Dialog::caretFrame {};

void Dialog::Initialize()
{
    Deactivate();
}

void Dialog::Uninitialize()
{
    if (textBuffer != nullptr)
    {
        al_destroy_bitmap(textBuffer);
    }
}

void Dialog::Logic()
{
    if(isActive)
    {
        frameScrollingTick++;
        if(frameScrollingTick >= FRAME_SCROLLING_TICKS_NEEDED)
        {
            frameScrollingTick = 0;
            textCol++;
            if(textCol >= TEXT_FIELD_COLS)
            {
                textCol = 0;
                textRow++;
                if(textRow >= TEXT_FIELD_ROWS)
                {
                    /// Todo
                }

            }

            caretFrame++;
            if(caretFrame > 1)
                caretFrame = 0;
        }
    }
}

void Dialog::Drawing()
{
    if (isActive)
    {
        al_draw_bitmap(Image::dialogFramePng, FRAME_X, FRAME_Y, 0);
        al_draw_bitmap_region(textBuffer, 
            textBufferXPosition, textBufferYPosition, 
            TEXT_FIELD_WIDTH, TEXT_FIELD_HEIGHT,
            TEXT_FIELD_X, TEXT_FIELD_Y, 0);

        al_draw_bitmap(Image::dialogCaretSub[caretFrame], TEXT_FIELD_X + textCol*Tile::HALF_WIDTH, TEXT_FIELD_Y, 0);
    }
}

void Dialog::Input()
{
}

void Dialog::Activate(std::string text_content)
{
    if (isActive || textBuffer != nullptr)
        Deactivate();

    isActive = true;

    textBufferXPosition = 0;
    textBufferYPosition = 0;
    text = text_content;
    textNumRows = Util::count_num_lines_will_render(FONTDEF_DIALOG, TEXT_FIELD_WIDTH, text);

    std::cout << "Deubg - Dialog: textNumRows = " << textNumRows << std::endl;
    textBuffer = al_create_bitmap(TEXT_FIELD_WIDTH, textNumRows * TEXT_FIELD_ROW_HEIGHT);

    ALLEGRO_BITMAP *previousTargetBitmap = al_get_target_bitmap();
    al_set_target_bitmap(textBuffer);
    Util::string_al_draw_multiline_text(FONTDEF_DIALOG, COLKEY_DIALOG_TEXT,
                                        0, 0, TEXT_FIELD_WIDTH, TEXT_FIELD_ROW_HEIGHT, ALLEGRO_ALIGN_LEFT,
                                        text);
    al_set_target_bitmap(previousTargetBitmap);
    al_draw_bitmap(textBuffer, TEXT_FIELD_X, TEXT_FIELD_Y, 0);

    textCol = 0;
    textRow = 0;

    frameScrollingTick = 0;
}

void Dialog::Deactivate()
{
    isActive = false;

    if (textBuffer != nullptr)
        al_destroy_bitmap(textBuffer);

    textBuffer = nullptr;

}

void Dialog::Advance()
{
    textRow += TEXT_ADVANCE_ROWS;
    textBufferYPosition += TEXT_FIELD_ROW_HEIGHT * TEXT_ADVANCE_ROWS;

    if(textRow >= textNumRows)
        Deactivate();
}