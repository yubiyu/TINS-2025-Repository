#pragma once

#include "configuration.h"

#include "image.h"

#include "cellindex.h"
#include "actorindex.h"

#include "direction.h"

#include <string>
#include <sstream>

#include <iostream>
#include <iomanip> // For setw

#include <algorithm>

struct Area
{
    static constexpr const char* STARTING_AREA = "1";

    enum enumDomains
    {
        DOMAIN_SULWON = 0,
        DOMAIN_RUWON = 1,
        DOMAIN_YION = 2
    };

    static const int COLS = 10;
    static const int ROWS = 8;

    static int roomBlueprint[COLS*ROWS];
    static int currentRoom[COLS*ROWS];
    static int previousRoom[COLS*ROWS]; // Used for the scrolling room transition effect.

    static int defaultSpawnCol, defaultSpawnRow;

    static std::string adjacentRooms[Direction::NUM_DIRECTIONS];

    static bool inRoomTransition;
    static int roomTransitionEffect;
    enum enumRoomTransitionEffects
    {
        ROOM_TRANSITION_TRANSLATION = 0,
        ROOM_TRANSITION_TELEPORT_INSTANT = 1
    };
    static int roomTransitionDirection;
    static const int ROOM_TRANSITION_X_SPEED = Tile::WIDTH*COLS / ActorIndex::WALK_DURATION; // This value should be proportional to the time it takes the Actor to move one tile.
    static const int ROOM_TRANSITION_Y_SPEED = Tile::HEIGHT*ROWS / ActorIndex::WALK_DURATION;

    static float currentRoomXPosition, currentRoomYPosition;
    static float previousRoomXPosition, previousRoomYPosition;

    static void Initialize(const char* room);
    static void Uninitialize();
    static void LoadRoomBlueprint(const char* room);
    static void ParseToRoomBlueprint(int x, int y, int data);
    static void ConstructRoom();

    static void Logic();
    static void Drawing();

    static void ChangeRoom(std::string destination);
};
