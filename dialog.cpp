#include "dialog.h"

bool Dialog::isActive;

ALLEGRO_BITMAP *Dialog::textFieldBuffer;

int Dialog::textXPosition, Dialog::textYPosition;

std::string Dialog::text;

void Dialog::Initialize()
{
    isActive = false;

    textXPosition = 0;
    textYPosition = 0;

    textFieldBuffer = nullptr;
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
}

void Dialog::Drawing()
{
    if (isActive)
    {
        al_draw_bitmap(Image::dialogFramePng, FRAME_X, FRAME_Y, 0);
        al_draw_bitmap(textFieldBuffer, textXPosition, textYPosition, 0);
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

    text = text_content;
    textXPosition = TEXT_FIELD_X;
    textYPosition = TEXT_FIELD_Y;

    int textFieldBufferLines = Util::count_num_lines_will_render(FONTDEF_DIALOG, TEXT_FIELD_WIDTH, text);
    std::cout << "Dialog: Debug: Activate dialog num lines = " << textFieldBufferLines << std::endl;
    textFieldBuffer = al_create_bitmap(TEXT_FIELD_WIDTH, textFieldBufferLines * TEXT_LINE_HEIGHT);

    ALLEGRO_BITMAP *previousTargetBitmap = al_get_target_bitmap();
    al_set_target_bitmap(textFieldBuffer);
    Util::string_al_draw_multiline_text(FONTDEF_DIALOG, COLKEY_DIALOG_TEXT,
                                        0, 0, TEXT_FIELD_WIDTH, TEXT_LINE_HEIGHT, ALLEGRO_ALIGN_LEFT,
                                        text);
    al_set_target_bitmap(previousTargetBitmap);
    al_draw_bitmap(textFieldBuffer, TEXT_FIELD_X, TEXT_FIELD_Y, 0);
}

void Dialog::Deactivate()
{
    isActive = false;

    if (textFieldBuffer != nullptr)
        al_destroy_bitmap(textFieldBuffer);

    textFieldBuffer = nullptr;
}