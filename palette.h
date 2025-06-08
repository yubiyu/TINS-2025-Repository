#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h>

#define COLKEY_BACKGROUND                                   Palette::COL_GB[Palette::palettePreset][0]

#define COLKEY_DEBUG_GRID_UNDERLAY                          Palette::COL_GB[Palette::palettePreset][1]

#define COLKEY_TEXT_TITLE                                   Palette::COL_GB[Palette::palettePreset][2]

#define COLKEY_MENU_TEXT                                    Palette::COL_GB[Palette::palettePreset][1]
#define COLKEY_MENU_TEXT_HIGHLIGHTED                        Palette::COL_GB[Palette::palettePreset][3]

#define COLKEY_DIALOG_TEXTFIELD                             Palette::COL_GB[Palette::palettePreset][3] 
#define COLKEY_DIALOG_TEXT                                  Palette::COL_GB[Palette::palettePreset][1]
#define COLKEY_DIALOG_TEXT_HIGHLIGHTED                      Palette::COL_GB[Palette::palettePreset][1]

#define COLKEY_STATUS_FRAME_TEXT                            Palette::COL_GB[Palette::palettePreset][0]

#define COLKEY_DEBUG_TEXT                                   Palette::COL_GB[Palette::palettePreset][1]
#define COLKEY_DEBUG_TEXT_HIGHLIGHTED                       Palette::COL_GB[Palette::palettePreset][3]

#include "util.h"

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
        {COL_GB_GREEN,   "Default"},
        {COL_GB_BLUE,    "B"},
        {COL_GB_VIOLET,  "C"},
        {COL_GB_MAGENTA, "D"},
        {COL_GB_RED,     "E"},
        {COL_GB_YELLOW,  "F"}
    };

    static ALLEGRO_COLOR COL_GB_BASE[COL_GB_NUM_COLOURS];
    static ALLEGRO_COLOR COL_GB[COL_GB_NUM_SWAPS][COL_GB_NUM_COLOURS];

    static int palettePreset;

    static ALLEGRO_COLOR transparentColour;

    static void InitializeGB();
    static void SwapPalette(int palette_swap);
};
