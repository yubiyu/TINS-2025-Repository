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

#include "util.h"

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

    static ALLEGRO_COLOR COL_GB[COL_GB_NUM_SWAPS][COL_GB_NUM_COLOURS];

    static int palettePreset;

    static ALLEGRO_COLOR transparentColour;

    static inline void InitializeGB()
    {
        for(size_t preset = 0; preset < COL_GB_NUM_SWAPS; preset++)
        {
            COL_GB[preset][0] = al_color_hsl( (200 + 60*preset)%360, 0.60f, 0.07f);
            COL_GB[preset][1] = al_color_hsl( (159 + 60*preset)%360, 0.33f, 0.30f);
            COL_GB[preset][2] = al_color_hsl( (102 + 60*preset)%360, 0.38f, 0.59f);
            COL_GB[preset][3] = al_color_hsl( ( 96 + 60*preset)%360, 0.74f, 0.89f);
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
