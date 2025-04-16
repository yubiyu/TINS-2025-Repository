#include "title.h"

int Title::optionTextX[NUM_OPTIONS];
int Title::optionTextY[NUM_OPTIONS];

int Title::targetedOption;
bool Title::exitOptionSelected;


void Title::Initialize()
{
    for(int i = 0; i < NUM_OPTIONS; i++)
    {
        optionTextX[i] = OPTION_TEXT_X_BASE;
        optionTextY[i] = OPTION_TEXT_Y_BASE + i*OPTION_TEXT_Y_SPACING;
    }

    SetTargetedOption(OPTION_NEW_GAME);
    exitOptionSelected = false;
}

void Title::Logic()
{

}

void Title::Input()
{
    if(Keyboard::keyHoldTicks[Keyboard::KEY_UP] == 1)
    {
        Title::AdjustTargetedOptionUp();
    }
    else if(Keyboard::keyHoldTicks[Keyboard::KEY_DOWN] == 1)
    {
        Title::AdjustTargetedOptionDown();
    }

    if(Keyboard::keyHoldTicks[Keyboard::KEY_ESC] == 1)
    {
        Title::SetTargetedOption(Title::OPTION_EXIT);
    }
    else if(Keyboard::keyHoldTicks[Keyboard::KEY_ENTER] == 1)
    {
        switch(Title::targetedOption)
        {
        case Title::OPTION_NEW_GAME:
            Scene::ChangeScene(Scene::SCENE_WORLDVIEW);
            break;
        case Title::OPTION_LOAD_GAME:
            Scene::ChangeScene(Scene::SCENE_WORLDVIEW);
            break;
        case Title::OPTION_ARCHIVE:
            Scene::ChangeScene(Scene::SCENE_ARCHIVE);
            break;
        case Title::OPTION_SETTINGS:
            Scene::ChangeScene(Scene::SCENE_SETTINGS);
            break;
        case Title::OPTION_EXIT:
            exitOptionSelected = true;
            break;
        }
    }
}

void Title::Drawing()
{
    al_draw_bitmap(Image::titleImagePng, TITLE_IMAGE_X, TITLE_IMAGE_Y, 0);

    al_draw_text(Text::publicPixel16, COLKEY_TEXT_TITLE, TITLE_TEXT_X, TITLE_TEXT_Y, 0, TITLE_TEXT);

    al_draw_bitmap(Image::menuOptionMarkerPng,
                   optionTextX[Title::targetedOption] - Menu::OPTION_MARKER_SPRITE_X_SPACING,
                   optionTextY[Title::targetedOption],
                   0);

    for(int i = 0; i < Title::NUM_OPTIONS; i++)
    {
        if(targetedOption == i)
        {
            Util::string_al_draw_text(FONTDEF_MENU_OPTION, COLKEY_TEXT_VALUE_HIGHLIGHTED,
                                 Title::optionTextX[i], Title::optionTextY[i],
                                 ALLEGRO_ALIGN_LEFT, Title::optionStrings.at(i));
        }
        else
            Util::string_al_draw_text(FONTDEF_MENU_OPTION, COLKEY_TEXT_VALUE,
                                 Title::optionTextX[i], Title::optionTextY[i],
                                 ALLEGRO_ALIGN_LEFT, Title::optionStrings.at(i));
    }
}


void Title::AdjustTargetedOptionUp()
{
    if(targetedOption > FIRST_OPTION)
        targetedOption --;
}

void Title::AdjustTargetedOptionDown()
{
    if(targetedOption < LAST_OPTION)
        targetedOption ++;
}

void Title::SetTargetedOption(int whichOption)
{
    targetedOption = whichOption;
}
