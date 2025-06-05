#include "text.h"

ALLEGRO_FONT *Text::builtin8;
ALLEGRO_FONT *Text::publicPixel8;
ALLEGRO_FONT *Text::publicPixel16;

void Text::Initialize()
{
    al_init_font_addon();
    al_init_ttf_addon();
    LoadResources();
}

void Text::Uninitialize()
{
    UnloadResources();
    al_shutdown_ttf_addon();
    al_shutdown_font_addon();
}

void Text::LoadResources()
{
    builtin8 = al_create_builtin_font();
    publicPixel8 = al_load_ttf_font("PublicPixel.ttf", Tile::HALF_HEIGHT, 0);
    publicPixel16 = al_load_ttf_font("PublicPixel.ttf", Tile::HEIGHT, 0);
}

void Text::UnloadResources()
{
    al_destroy_font(builtin8);
    al_destroy_font(publicPixel8);
    al_destroy_font(publicPixel16);
}
