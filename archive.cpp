#include "archive.h"

// std::string Archive::returnToTitleString;

int Archive::currentCategory;
int Archive::currentSection;

void Archive::Logic()
{
}

void Archive::Input()
{
    if (Keyboard::keyHoldTicks[Keyboard::KEY_ESC] == 1 || Keyboard::keyHoldTicks[Keyboard::KEY_ENTER] == 1)
    {
        Scene::ChangeScene(Scene::SCENE_TITLE);
    }
}

void Archive::Drawing()
{
    al_draw_bitmap(Image::archivePlaceholderPng, 0, 0, 0);
}
