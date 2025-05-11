#pragma once

#include "image.h"

#include <string>

struct Dialog
{
    static float frameXPosition, frameYPosition;
    static int textXPosition, textYPosition;

    static std::string text;

    static void Initialize()
    {

    }

    static void Logic()
    {
    }

    static void Drawing()
    {
        al_draw_bitmap(Image::dialogFramePng, frameXPosition, frameYPosition, 0);
    }


    static void Input()
    {

    }


};
