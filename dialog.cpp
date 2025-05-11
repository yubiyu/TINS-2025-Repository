#include "dialog.h"

bool Dialog::isActive;

ALLEGRO_BITMAP *Dialog::textBuffer;

int Dialog::textXPosition, Dialog::textYPosition;

std::string Dialog::text;

void Dialog::Initialize()
{
    isActive = false;

    textXPosition = 0;
    textYPosition = 0;

    textBuffer = nullptr;
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
}

void Dialog::Drawing()
{
    if (isActive)
    {
        al_draw_bitmap(Image::dialogFramePng, FRAME_X, FRAME_Y, 0);
        al_draw_bitmap(textBuffer, textXPosition, textYPosition, 0);
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

    text = text_content;
    textXPosition = TEXT_FIELD_X;
    textYPosition = TEXT_FIELD_Y;

    textBuffer = al_create_bitmap(TEXT_FIELD_WIDTH,
                                  Util::count_num_lines_will_render(FONTDEF_DIALOG, TEXT_FIELD_WIDTH, text) * TEXT_LINE_HEIGHT);

    ALLEGRO_BITMAP *targetBitmap = al_get_target_bitmap();
    al_set_target_bitmap(textBuffer);
    Util::string_al_draw_multiline_text(FONTDEF_DIALOG, COLKEY_TEXT_VALUE,
                                        textXPosition, textYPosition, TEXT_FIELD_WIDTH, TEXT_LINE_HEIGHT, ALLEGRO_ALIGN_LEFT,
                                        text);

    al_set_target_bitmap(targetBitmap); // Return to previous target.
}

void Dialog::Deactivate()
{
    isActive = false;

    if (textBuffer != nullptr)
        al_destroy_bitmap(textBuffer);

    textBuffer = nullptr;
}