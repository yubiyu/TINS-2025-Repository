#pragma once

#include "direction.h"
#include "tile.h"

struct ActorIndex
{
    enum enumActorSpriteIDs
    {
        SPRITE_EYES = 0,
        SPRITE_OWL = 1,
        SPRITE_GNAW = 2
    };
    static const int MARKER_SPRITE_ID_BEGIN = SPRITE_EYES;
    static const int MARKER_SPRITE_ID_END = SPRITE_GNAW;
    static const int NUM_SPRITE_IDS = MARKER_SPRITE_ID_END + 1;

    static constexpr float WALK_SPEED_BASE = 1.0;
    static const int WALK_DURATION = Tile::WIDTH / WALK_SPEED_BASE; // In logic ticks. 

    enum enumActions
    {
        ACTION_WALK = 0,
        ACTION_STAND = 1
    };
    static const int MARKER_ACTION_END = ACTION_STAND;
    static const int NUM_ACTIONS = MARKER_ACTION_END + 1;

    static const int NUM_WALK_FRAMES = 4;
    static const int WALK_SUB_BITMAPS_COLS = Direction::NUM_DIRECTIONS * NUM_WALK_FRAMES;
    //static const int NUM_WALK_SUB_BITMAPS = NUM_SPRITE_IDS * NUM_FACING_DIRS * NUM_WALK_FRAMES;
    static const int NUM_STAND_FRAMES = 1;
    static const int STAND_SUB_BITMAPS_COLS = Direction::NUM_DIRECTIONS * NUM_STAND_FRAMES;
    //static const int NUM_STAND_SUB_BITMAPS = NUM_SPRITE_IDS * NUM_FACING_DIRS * NUM_STAND_FRAMES;
    static const int WALK_STAND_FRAME_INDEX = 1; // 0, [1], 2

    static const int BASE_FRAME_DELAY = 8;


};
