#include "display.h"
#include "tile.h"

#include "image.h"

#include "pc.h"

struct StatsFrame
{
    static constexpr float X_POSITION = 0;
    static constexpr float Y_POSITION = Display::NATIVE_HEIGHT - Tile::HEIGHT;

    static void Initialize();
    static void Uninitialize();

    static void Logic();
    static void Drawing();
    static void Input();
};