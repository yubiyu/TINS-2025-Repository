#include "dialog.h"

bool Dialog::isActive{};
bool Dialog::isScrolling{};

std::string Dialog::text{};
ALLEGRO_BITMAP *Dialog::textBuffer{};
int Dialog::textBufferXPosition{}, Dialog::textBufferYPosition{};

int Dialog::textFieldRow{};
int Dialog::textBufferNumRows{};

int Dialog::revealedRow{};
int Dialog::revealedCol{};

int Dialog::frameScrollingTick{};

int Dialog::caretFrame{};

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
    if (isActive)
    {
        if (isScrolling)
        {
            frameScrollingTick++;
            if (frameScrollingTick >= FRAME_SCROLLING_TICKS_NEEDED)
            {
                frameScrollingTick = 0;
                revealedCol++;
                if (revealedCol >= TEXT_FIELD_COLS)
                {
                    revealedCol = 0;
                    revealedRow++;
                }

                if (revealedRow > TEXT_FIELD_ROWS - 1)
                    isScrolling = false;

                caretFrame++;
                if (caretFrame > 1)
                    caretFrame = 0;
            }
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

        if (isScrolling)
        {
            if (revealedRow <= TEXT_FIELD_ROWS - 1)
            {
                al_draw_filled_rectangle(TEXT_FIELD_X, TEXT_FIELD_Y + (revealedRow + 1) * TEXT_FIELD_ROW_HEIGHT,
                                         TEXT_FIELD_X + TEXT_FIELD_WIDTH, TEXT_FIELD_Y + TEXT_FIELD_HEIGHT,
                                         COLKEY_DIALOG_TEXTFIELD);

                if (revealedCol <= TEXT_FIELD_COLS - 1)
                    al_draw_filled_rectangle(TEXT_FIELD_X + revealedCol * Tile::HALF_WIDTH, TEXT_FIELD_Y + revealedRow * TEXT_FIELD_ROW_HEIGHT,
                                             TEXT_FIELD_X + TEXT_FIELD_WIDTH, TEXT_FIELD_Y + TEXT_FIELD_HEIGHT,
                                             COLKEY_DIALOG_TEXTFIELD);
            }

            
            al_draw_bitmap(Image::dialogCaretSub[caretFrame],
                           TEXT_FIELD_X + revealedCol * Tile::HALF_WIDTH,
                           TEXT_FIELD_Y + revealedRow * TEXT_FIELD_ROW_HEIGHT, 0);
        }
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
    isScrolling = true;

    textBufferXPosition = 0;
    textBufferYPosition = 0;
    text = text_content;
    textBufferNumRows = Util::count_multiline_rows(FONTDEF_DIALOG, TEXT_FIELD_WIDTH, text);

    textBuffer = al_create_bitmap(TEXT_FIELD_WIDTH, textBufferNumRows * TEXT_FIELD_ROW_HEIGHT);

    ALLEGRO_BITMAP *previousTargetBitmap = al_get_target_bitmap();
    al_set_target_bitmap(textBuffer);
    Util::string_al_draw_multiline_text(FONTDEF_DIALOG, COLKEY_DIALOG_TEXT,
                                        0, 0, TEXT_FIELD_WIDTH, TEXT_FIELD_ROW_HEIGHT, ALLEGRO_ALIGN_LEFT,
                                        text);
    al_set_target_bitmap(previousTargetBitmap);
    al_draw_bitmap(textBuffer, TEXT_FIELD_X, TEXT_FIELD_Y, 0);

    textFieldRow = 0;
    revealedRow = 0;
    revealedCol = 0;

    frameScrollingTick = 0;
}

void Dialog::Deactivate()
{
    isActive = false;
    isScrolling = false;

    if (textBuffer != nullptr)
        al_destroy_bitmap(textBuffer);

    textBuffer = nullptr;
}

void Dialog::Advance()
{
    if (!isScrolling && 
        textFieldRow + TEXT_FIELD_ROWS - 1 >= textBufferNumRows - 1)
    {
        Deactivate();
        return;
    }
    else if(revealedRow < TEXT_FIELD_ROWS - 1)
    {
        revealedRow = TEXT_FIELD_ROWS;
        revealedCol = TEXT_FIELD_COLS;
        isScrolling = false;
    }
    else
    {
        isScrolling = true;

        textFieldRow += TEXT_ADVANCE_ROWS;
        textBufferYPosition += TEXT_FIELD_ROW_HEIGHT * TEXT_ADVANCE_ROWS;

        revealedRow = 0;
        revealedCol = 0;
    }
}