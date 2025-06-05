#include "loadgame.h"

void LoadGame::Logic()
{
}

void LoadGame::Input()
{
    if (Keyboard::keyHoldTicks[Keyboard::KEY_ESC] == 1)
    {
        Scene::ChangeScene(Scene::SCENE_TITLE);
    }
}

void LoadGame::Drawing()
{
    al_draw_bitmap(Image::loadgamePlaceholderPng, 0, 0, 0);
}