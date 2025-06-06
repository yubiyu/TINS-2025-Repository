#include "palette.h"

ALLEGRO_COLOR Palette::COL_GB[COL_GB_NUM_SWAPS][COL_GB_NUM_COLOURS];
ALLEGRO_COLOR Palette::COL_GB_BASE[COL_GB_NUM_COLOURS];

int Palette::palettePreset;

ALLEGRO_COLOR Palette::transparentColour;

void Palette::InitializeGB()
{
    ///COL_GB_BASE[0] = al_map_rgb(8, 24, 32);
    ///COL_GB_BASE[1] = al_map_rgb(52, 104, 86);
    ///COL_GB_BASE[2] = al_map_rgb(136, 192, 112);
    ///COL_GB_BASE[3] = al_map_rgb(224, 248, 208);
    
    COL_GB_BASE[0] = al_map_rgb(62, 58, 66);
    COL_GB_BASE[1] = al_map_rgb(135, 114, 134);
    COL_GB_BASE[2] = al_map_rgb(240, 182, 149);
    COL_GB_BASE[3] = al_map_rgb(233, 245, 218);
    
    std::cout << std::endl;

    for (size_t preset = 0; preset < COL_GB_NUM_SWAPS; preset++)
    {
        for (size_t i = 0; i < COL_GB_NUM_COLOURS; i++)
        {
            float r, g, b;
            al_unmap_rgb_f(COL_GB_BASE[i], &r, &g, &b);

            float targetHue, targetSaturation, targetLightness;
            al_color_rgb_to_hsl(r, g, b, &targetHue, &targetSaturation, &targetLightness);

            COL_GB[preset][i] = al_color_hsl(std::fmod(targetHue + 60.0f * (float)preset, 360.0f), targetSaturation, targetLightness);
            Util::al_round_rgb(&COL_GB[preset][i]);
        }
    }

    palettePreset = COL_GB_FIRST;

    transparentColour = al_map_rgba(0, 0, 0, 0);
}

void Palette::SwapPalette(int palette_swap)
{
    palettePreset = palette_swap;

    if (palettePreset < COL_GB_FIRST)
        palettePreset = COL_GB_FIRST;
    else if (palettePreset > COL_GB_LAST)
        palettePreset = COL_GB_LAST;
}
