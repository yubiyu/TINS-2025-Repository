#pragma once

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "tile.h"

#define FONTDEF_MENU_OPTION                 Text::publicPixel8

struct Text
{
    static const int HEIGHT_8 = 8;
    static const int HEIGHT_16 = 16;
    static const int NUM_FONT_SIZES = 2;

    static ALLEGRO_FONT *builtin8;
    static ALLEGRO_FONT *publicPixel8;
    static ALLEGRO_FONT *publicPixel16;

    static void Initialize();
    static void Uninitialize();

    static void LoadResources();
    static void UnloadResources();
};
