#pragma once

#include "configuration.h"

#include "camera.h"

#include "image.h"

#include "cellindex.h"
#include "featureindex.h"
#include "actorindex.h"

#include "foodindex.h"

#include "direction.h"

#include "dialog.h"

#include <string>
#include <sstream>

#include <iostream>
#include <iomanip> // For setw

#include <algorithm>

#include <array>
#include <unordered_map>

struct Area
{
    /// BEGIN WORLD GRID DATA ///
    static std::string worldRoomID;
    static constexpr const char *VOID_ROOM_ID = "xxxx";

    static const int WORLD_GRID_LAYERS = 7;
    static const int WORLD_GRID_LAYER_ROWS = 3; // The number of worldGrid rows in a layer.
    
    static const int WORLD_GRID_COLS = 3;
    static const int WORLD_GRID_ROWS = WORLD_GRID_LAYERS*WORLD_GRID_LAYER_ROWS;

    static std::string worldGrid[WORLD_GRID_COLS * WORLD_GRID_ROWS];

    static int worldGridCurrentCol, worldGridCurrentRow;

    static constexpr float LAYER_SEPARATION_RATIO = 1.5;
    /// END WORLD GRID DATA ///
    /// BEGIN ROOM DATA ///
    static const int ROOM_COLS = 10; // tiles across
    static const int ROOM_ROWS = 8;  // tiles high
    static constexpr int ROOM_AREA = ROOM_COLS * ROOM_ROWS;

    static std::array<int, ROOM_AREA> roomCellBlueprint;
    static std::array<int, ROOM_AREA> roomFeatureBlueprint;
    static std::array<int, ROOM_AREA> currentRoomCells;
    static std::array<int, ROOM_AREA> currentRoomFeatures;
    static std::array<int, ROOM_AREA> previousRoomCells; // Used for the scrolling room transition effect.
    static std::array<int, ROOM_AREA> previousRoomFeatures; // Used for the scrolling room transition effect.

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
    static const int ROOM_TRANSITION_ASCEND_DELAY = ActorIndex::WALK_DURATION * 2;
    static const int ROOM_TRANSITION_DESCEND_DELAY = ActorIndex::WALK_DURATION * 2;

    static const int ROOM_TRANSITION_X_SPEED = Tile::WIDTH * ROOM_COLS / ActorIndex::WALK_DURATION; // This value should be proportional to the time it takes the Actor to move one tile.
    static const int ROOM_TRANSITION_Y_SPEED = Tile::HEIGHT * ROOM_ROWS / ActorIndex::WALK_DURATION;

    static float currentRoomXPosition, currentRoomYPosition;
    static float previousRoomXPosition, previousRoomYPosition;
    /// END ROOM DATA ///
    /// BEGIN OBJECTIVES ///
    static const int WORLD_NUM_CHESTS = 53;
    static const int MAX_CHESTS_PER_ROOM = 3;

    static std::unordered_map<std::string, std::array<bool,Area::MAX_CHESTS_PER_ROOM>>worldChestsLooted;
    static bool currentRoomChestsLooted[MAX_CHESTS_PER_ROOM];
    static bool previousRoomChestsLooted[MAX_CHESTS_PER_ROOM];

    static int chestsLootedCount;
    /// END OBJECTIVES ///

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

    static void AscendLayer(); // Note that ascending a layer actually makes the world grid row go down.
    static void DescendLayer(); // Note that descending a layer actually makes the world grid row go up.
};
