#include "dialog.h"

bool Dialog::isActive {};

ALLEGRO_BITMAP *Dialog::textFieldBuffer {};

int Dialog::textXPosition {}, Dialog::textYPosition {};

std::string Dialog::text {};

int Dialog::currentTextRow {};
int Dialog::currentTextCol {};
int Dialog::textNumRows {};
int Dialog::frameScrollingTick {};

int Dialog::caretFrame {};

void Dialog::Initialize()
{
    Deactivate();
}

void Dialog::Uninitialize()
{
    if (textFieldBuffer != nullptr)
    {
        al_destroy_bitmap(textFieldBuffer);
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
            currentTextCol++;
            if(currentTextCol >= TEXT_FIELD_COLS)
            {
                currentTextCol = 0;
                currentTextRow++;
                if(currentTextRow >= TEXT_FIELD_ROWS)
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
        al_draw_bitmap(textFieldBuffer, textXPosition, textYPosition, 0);

        al_draw_bitmap(Image::dialogCaretSub[caretFrame], TEXT_FIELD_X + currentTextCol*Tile::HALF_WIDTH, TEXT_FIELD_Y, 0);
    }
}

void Dialog::Input()
{
}

void Dialog::Activate(std::string text_content)
{
    if (isActive || textFieldBuffer != nullptr)
        Deactivate();

    isActive = true;

    textXPosition = TEXT_FIELD_X;
    textYPosition = TEXT_FIELD_Y;
    text = text_content;
    textNumRows = Util::count_num_lines_will_render(FONTDEF_DIALOG, TEXT_FIELD_WIDTH, text);

    std::cout << "Deubg - Dialog: textNumRows = " << textNumRows << std::endl;
    textFieldBuffer = al_create_bitmap(TEXT_FIELD_WIDTH, textNumRows * TEXT_FIELD_ROW_HEIGHT);

    ALLEGRO_BITMAP *previousTargetBitmap = al_get_target_bitmap();
    al_set_target_bitmap(textFieldBuffer);
    Util::string_al_draw_multiline_text(FONTDEF_DIALOG, COLKEY_DIALOG_TEXT,
                                        0, 0, TEXT_FIELD_WIDTH, TEXT_FIELD_ROW_HEIGHT, ALLEGRO_ALIGN_LEFT,
                                        text);
    al_set_target_bitmap(previousTargetBitmap);
    al_draw_bitmap(textFieldBuffer, TEXT_FIELD_X, TEXT_FIELD_Y, 0);

    currentTextCol = 0;
    currentTextRow = textNumRows;
    if(currentTextRow > TEXT_FIELD_ROWS)
        currentTextRow = TEXT_FIELD_COLS; // Make currentTextRow the bottom row of the text field.

    frameScrollingTick = 0;
}

void Dialog::Deactivate()
{
    isActive = false;

    if (textFieldBuffer != nullptr)
        al_destroy_bitmap(textFieldBuffer);

    textFieldBuffer = nullptr;

}