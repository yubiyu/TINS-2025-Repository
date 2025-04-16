#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h>

#define COLKEY_BACKGROUND                                   Palette::COL_GB[Palette::palettePreset][0]

#define COLKEY_DEBUG_GRID_UNDERLAY                          Palette::COL_GB[Palette::palettePreset][1]

#define COLKEY_TEXT_TITLE                                   Palette::COL_GB[Palette::palettePreset][2]
//#define COLKEY_TEXT_HEADER                                Palette::COL_GB[Palette::palettePreset][2]
//#define COLKEY_TEXT_LABEL                                 Palette::COL_GB[Palette::palettePreset][2]
#define COLKEY_TEXT_VALUE                                   Palette::COL_GB[Palette::palettePreset][1]
#define COLKEY_TEXT_VALUE_HIGHLIGHTED                       Palette::COL_GB[Palette::palettePreset][3]
#define COLKEY_TEXT_DESCRIPTION                             Palette::COL_GB[Palette::palettePreset][2]

#include "core/util.h"

#include <cmath>
#include <string>
#include <unordered_map>
#include <iostream>

struct Palette
{
    static const int COL_GB_NUM_COLOURS = 4;
    enum enumCOL_GBPaletteSwaps
    {
        COL_GB_GREEN = 0,
        COL_GB_BLUE = 1,
        COL_GB_VIOLET = 2,
        COL_GB_MAGENTA = 3,
        COL_GB_RED = 4,
        COL_GB_YELLOW = 5
    };
    static const int COL_GB_FIRST = COL_GB_GREEN;
    static const int COL_GB_LAST = COL_GB_YELLOW;
    static const int COL_GB_NUM_SWAPS = COL_GB_LAST+1;
    static const inline std::unordered_map<int, std::string>palettePresetNames =
    {
        {COL_GB_GREEN,   "Green"},
        {COL_GB_BLUE,    "Blue"},
        {COL_GB_VIOLET,  "Violet"},
        {COL_GB_MAGENTA, "Magenta"},
        {COL_GB_RED,     "Red"},
        {COL_GB_YELLOW,  "Yellow"}
    };

    static ALLEGRO_COLOR COL_GB_BASE[COL_GB_NUM_COLOURS];
    static ALLEGRO_COLOR COL_GB[COL_GB_NUM_SWAPS][COL_GB_NUM_COLOURS];

    static int palettePreset;

    static ALLEGRO_COLOR transparentColour;

    static inline void InitializeGB()
    {
        COL_GB_BASE[0] = al_map_rgb(  8,  24,  32);
        //std::cout << "Debug [base col]: r=" << COL_GB_BASE[0].r << " g=" << COL_GB_BASE[0].g << " b=" << COL_GB_BASE[0].b << std::endl;
        COL_GB_BASE[1] = al_map_rgb( 52, 104,  86);
        COL_GB_BASE[2] = al_map_rgb(136, 192, 112);
        COL_GB_BASE[3] = al_map_rgb(224, 248, 208);
        std::cout << std::endl;

        for(size_t preset = 0; preset < COL_GB_NUM_SWAPS; preset++)
        {
            for(size_t i = 0; i < COL_GB_NUM_COLOURS; i++)
            {
                float r, g, b;
                al_unmap_rgb_f(COL_GB_BASE[i], &r, &g, &b);
                //std::cout << "Debug [unmapped col]: r=" << r << " g=" << g << " b=" << b << std::endl;

                float targetHue, targetSaturation, targetLightness;
                al_color_rgb_to_hsl(r, g, b, &targetHue, &targetSaturation, &targetLightness);

                COL_GB[preset][i] = al_color_hsl( std::fmod(targetHue+60.0f*(float)preset, 360.0f), targetSaturation, targetLightness);
                COL_GB[preset][i] = al_map_rgb( (char)(255.0f * COL_GB[preset][i].r + 0.5f / 255.0f),
                                                (char)(255.0f * COL_GB[preset][i].g + 0.5f / 255.0f),
                                                (char)(255.0f * COL_GB[preset][i].b + 0.5f / 255.0f));

                //std::cout << "Debug [hsl'ed col]: r=" << COL_GB[preset][i].r << " g=" << COL_GB[preset][i].g << " b=" << COL_GB[preset][i].b << std::endl;
            }
            //std::cout << std::endl;
        }

        palettePreset = COL_GB_FIRST;

        transparentColour = al_map_rgba(0, 0, 0, 0);
    }

    static inline void SwapPalette(int palette_swap)
    {
        palettePreset = palette_swap;

        if(palettePreset < COL_GB_FIRST)
            palettePreset = COL_GB_FIRST;
        else if(palettePreset > COL_GB_LAST)
            palettePreset = COL_GB_LAST;
    }
};
