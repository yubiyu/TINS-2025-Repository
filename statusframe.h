#include "display.h"
#include "tile.h"

#include "image.h"

#include "pc.h"
#include "area.h"
#include "foodeater.h"

#include "util.h"

#include <sstream>
#include <iomanip>

struct StatusFrame
{
    // Position is relative to Display origin.
    static constexpr float FRAME_X_POSITION = 0;
    static constexpr float FRAME_Y_POSITION = Display::NATIVE_HEIGHT - Tile::HEIGHT;



    // Positions are relative to Frame_X/Y.
    //static constexpr float ICON_PC_LIFESPAN_X = Tile::WIDTH;
    //static constexpr float ICON_PC_LEVEL_X = Tile::WIDTH * 3;
    //static constexpr float ICON_AREA_LEVEL_X = Tile::WIDTH * 5;

    static constexpr float ICON_MOUTH_X_POSITION = Tile::WIDTH * 1.5;
    static constexpr float ICON_WINGS_X_POSITION = Tile::WIDTH * 4.5;

    static const int TEXT_Y_POSITION = Tile::HEIGHT/4;

    static const int TEXT_FOODEATER_NUTRITION_X_POSITION = Tile::HALF_WIDTH * 3; // ALLEGRO_ALIGN_RIGHT-ed.
    static const int TEXT_AREA_CHESTS_LOOTED_X_POSITION = Tile::WIDTH * 7;

    static constexpr float FOOD_ICONS_X_POSITION = Tile::WIDTH *3.5;

    static void Initialize();
    static void Uninitialize();

    static void Logic();
    static void Drawing();
    static void Input();
};