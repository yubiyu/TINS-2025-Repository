#include "display.h"
#include "tile.h"

#include "image.h"

#include "pc.h"

struct StatusFrame
{
    //Position is relative to Display origin. 
    static constexpr float FRAME_X_POSITION = 0;
    static constexpr float FRAME_Y_POSITION = Display::NATIVE_HEIGHT - Tile::HEIGHT;

    //Positions are relative to Frame_X/Y.
    static constexpr float ICON_PC_LIFESPAN_X = Tile::WIDTH;
    static constexpr float ICON_PC_LEVEL_X = Tile::WIDTH * 3;
    static constexpr float ICON_AREA_LEVEL_X = Tile::WIDTH * 5;

    static const int       TEXT_PC_HP_X = ICON_PC_LIFESPAN_X + Tile::HALF_WIDTH;
    static const int       TEXT_PC_LEVEL_X = ICON_PC_LEVEL_X + Tile::HALF_WIDTH;
    static const int       TEXT_AREA_LEVEL_X = ICON_AREA_LEVEL_X + Tile::HALF_WIDTH;

    static void Initialize();
    static void Uninitialize();

    static void Logic();
    static void Drawing();
    static void Input();
};