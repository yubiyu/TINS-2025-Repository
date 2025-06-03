#include "dialog.h"

bool Dialog::isActive{};
bool Dialog::isScrolling{};

std::string Dialog::text{};
ALLEGRO_BITMAP *Dialog::textBuffer{};
int Dialog::textBufferXPosition{}, Dialog::textBufferYPosition{};

int Dialog::textFieldTopRow{};
int Dialog::textBufferNumRows{};
std::vector<int> Dialog::textBufferRowWidths{};

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
                if (revealedCol >= TEXT_FIELD_COLS || (revealedCol >= textBufferRowWidths[textFieldTopRow + revealedRow] / TEXT_CHAR_WIDTH))
                {
                    revealedCol = 0;
                    revealedRow++;
                }

                if (revealedRow >= TEXT_FIELD_ROWS) // To clarify, revealedRow would have to be at least one line beyond the end of the text field.
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
            if (revealedRow < TEXT_FIELD_ROWS)
            {
                al_draw_filled_rectangle(TEXT_FIELD_X, TEXT_FIELD_Y + (revealedRow + 1) * TEXT_FIELD_ROW_HEIGHT,
                                         TEXT_FIELD_X + TEXT_FIELD_WIDTH, TEXT_FIELD_Y + TEXT_FIELD_HEIGHT,
                                         COLKEY_DIALOG_TEXTFIELD);

                if (revealedCol < TEXT_FIELD_COLS)
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
    if (isActive)
    {
        if (Keyboard::keyHoldTicks[Keyboard::KEY_Z] == 1)
            Advance();
        else if (Keyboard::keyHoldTicks[Keyboard::KEY_X] == 1)
            Deactivate();
    }
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
    textBufferRowWidths = Util::collect_multiline_widths(FONTDEF_DIALOG, TEXT_FIELD_WIDTH, text);

    textBuffer = al_create_bitmap(TEXT_FIELD_WIDTH, textBufferNumRows * TEXT_FIELD_ROW_HEIGHT);

    ALLEGRO_BITMAP *previousTargetBitmap = al_get_target_bitmap();
    al_set_target_bitmap(textBuffer);
    Util::string_al_draw_multiline_text(FONTDEF_DIALOG, COLKEY_DIALOG_TEXT,
                                        0, 0, TEXT_FIELD_WIDTH, TEXT_FIELD_ROW_HEIGHT, ALLEGRO_ALIGN_LEFT,
                                        text);
    al_set_target_bitmap(previousTargetBitmap);
    al_draw_bitmap(textBuffer, TEXT_FIELD_X, TEXT_FIELD_Y, 0);

    textFieldTopRow = 0;
    revealedRow = 0;
    revealedCol = 0;

    frameScrollingTick = 0;
}

void Dialog::Activate(const char *section, const char *key)
{
    Activate(Configuration::GetString(Configuration::dialogsCfg, section, key));
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
    if(isScrolling)
    {
            // Advance to the end of the current textbuffer region. Stop scrolling.
            revealedRow = TEXT_FIELD_ROWS;
            revealedCol = TEXT_FIELD_COLS;
            isScrolling = false;
    }
    else //!isScrolling
    {
        if(textFieldTopRow + TEXT_FIELD_ROWS >= textBufferNumRows)
        {
            Deactivate();
            return;
        }
        else
        {
            // Advance to the *next* textbuffer region (default: three rows ahead). 
            //Begin scrolling again.
            textFieldTopRow += TEXT_BUFFER_ADVANCE_ROWS;
            textBufferYPosition += TEXT_FIELD_ROW_HEIGHT * TEXT_BUFFER_ADVANCE_ROWS;

            revealedRow = 0;
            revealedCol = 0;

            isScrolling = true;
        }
    }
}