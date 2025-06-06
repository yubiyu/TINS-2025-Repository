#pragma once

#include "configuration.h"

#include "camera.h"

#include "image.h"

#include "cellindex.h"
#include "featureindex.h"
#include "actorindex.h"

#include "direction.h"

#include "dialog.h"

#include <string>
#include <sstream>

#include <iostream>
#include <iomanip> // For setw

#include <algorithm>

#include <array>
#include <map>

struct Area
{
    /// BEGIN WORLD GRID DATA ///
    static constexpr const char *VOID_ROOM_ID = "xxxx";

    static const int WORLD_LAYERS = 9;
    static const int WORLD_LAYER_ROWS = 3; // The number of worldGrid rows in a layer.
    
    static const int WORLD_COLS = 3;
    static const int WORLD_ROWS = WORLD_LAYERS*WORLD_LAYER_ROWS;

    static std::string worldGrid[WORLD_COLS * WORLD_ROWS];

    static int worldGridCurrentCol, worldGridCurrentRow;
    /// END WORLD GRID DATA ///
    /// BEGIN ROOM DATA ///
    static const int ROOM_COLS = 10; // Y
    static const int ROOM_ROWS = 8;  // X
    static constexpr int ROOM_AREA = ROOM_COLS * ROOM_ROWS;

    static std::array<int, ROOM_AREA> roomCellBlueprint;
    static std::array<int, ROOM_AREA> roomFeatureBlueprint;
    static std::array<int, ROOM_AREA> currentRoomCells;
    static std::array<int, ROOM_AREA> currentRoomFeatures;
    static std::array<int, ROOM_AREA> previousRoomCells; // Used for the scrolling room transition effect.
    static std::array<int, ROOM_AREA> previousRoomFeatures;

    static int roomSpawnCol, roomSpawnRow;

    static std::string adjacentRooms[Direction::NUM_DIRECTIONS];

    static bool inRoomTransition;
    static int roomTransitionEffect;
    enum enumRoomTransitionEffects
    {
        ROOM_TRANSITION_TRANSLATION = 0,
        ROOM_TRANSITION_TELEPORT_INSTANT = 1,
        ROOM_TRANSITION_ASCEND = 2,
        ROOM_TRANSITION_DESCEND = 3
    };

    static int roomTransitionDelay; // Pause before camera movement.
    static const int ROOM_TRANSITION_ASCEND_BASE_DELAY = ActorIndex::WALK_DURATION * 3;
    static const int ROOM_TRANSITION_DESCEND_BASE_DELAY = ActorIndex::WALK_DURATION * 3;

    static const int ROOM_TRANSITION_X_SPEED = Tile::WIDTH * ROOM_COLS / ActorIndex::WALK_DURATION; // This value should be proportional to the time it takes the Actor to move one tile.
    static const int ROOM_TRANSITION_Y_SPEED = Tile::HEIGHT * ROOM_ROWS / ActorIndex::WALK_DURATION;

    static float currentRoomXPosition, currentRoomYPosition;
    static float previousRoomXPosition, previousRoomYPosition;
    /// END ROOM DATA ///
    /// BEGIN PERSISTENT STATE AND SERIALIZATION
    static std::map<std::string, std::vector<bool>> featuresActive; // Add to/update this map as rooms are visited.
    /// END PERSISTENT STATE AND SERIALIZATION

    static void Initialize();
    static void Uninitialize();
    static void LoadWorldGrid(const char *worldgrid);
    static void LoadRoomBlueprints(int world_x, int world_y);
    static void ParseToRoomCellBlueprint(int x, int y, int data);
    static void LoadRoomFeatureBlueprint(int world_x, int world_y);
    static void ParseToRoomFeatureBlueprint(int x, int y, int data);
    static void ConstructRoom();
    static void UpdateRoomXYPositions();

    static void Logic();
    static void Drawing();

    static void ChangeRoom(int dest_x, int dest_y, int transition_effect);

    static bool RoomBoundaryCheck(int x, int y);
    static bool WalkObstacleCheck(int x, int y);
    static bool VoidCellCheck(int x, int y);
    static bool TeleporterCellCheck(int x, int y);

    static void ActivateFeature(int x, int y);

    static void AscendLayer();
    static void DescendLayer();
};
