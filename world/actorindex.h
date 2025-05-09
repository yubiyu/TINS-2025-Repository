#pragma once

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

    enum enumFacingDirections
    {
        FACING_DIR_UP = 0,
        FACING_DIR_DOWN = 1,
        FACING_DIR_LEFT = 2,
        FACING_DIR_RIGHT = 3
    };
    static const int MARKER_FACING_DIR_END = FACING_DIR_RIGHT;
    static const int NUM_FACING_DIRS = MARKER_FACING_DIR_END + 1;

    static constexpr float MOVE_SPEED_BASE = 1.0;

    enum enumActions
    {
        ACTION_WALK = 0,
        ACTION_STAND = 1
    };
    static const int MARKER_ACTION_END = ACTION_STAND;
    static const int NUM_ACTIONS = MARKER_ACTION_END + 1;

    static const int NUM_WALK_FRAMES = 4;
    //static const int NUM_WALK_SUB_BITMAPS = NUM_SPRITE_IDS * NUM_FACING_DIRS * NUM_WALK_FRAMES;
    static const int NUM_STAND_FRAMES = 1;
    //static const int NUM_STAND_SUB_BITMAPS = NUM_SPRITE_IDS * NUM_FACING_DIRS * NUM_STAND_FRAMES;
    static const int WALK_STAND_FRAME_INDEX = 1; // 0, [1], 2

    static const int BASE_FRAME_DELAY = 8;


};
