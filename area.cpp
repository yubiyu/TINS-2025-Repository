#include "area.h"

std::string Area::worldRoomID{};

std::string Area::worldGrid[WORLD_GRID_COLS * WORLD_GRID_ROWS];
int Area::worldGridCurrentCol{}, Area::worldGridCurrentRow{};

std::array<int, Area::ROOM_AREA> Area::roomCellBlueprint{};
std::array<int, Area::ROOM_AREA> Area::roomFeatureBlueprint{};
std::array<int, Area::ROOM_AREA> Area::currentRoomCells{};
std::array<int, Area::ROOM_AREA> Area::currentRoomFeatures{};
std::array<int, Area::ROOM_AREA> Area::previousRoomCells{};
std::array<int, Area::ROOM_AREA> Area::previousRoomFeatures{};

int Area::roomSpawnCol{}, Area::roomSpawnRow{};

std::string Area::adjacentRooms[Direction::NUM_DIRECTIONS];

bool Area::inRoomTransition{};
int Area::roomTransitionEffect{};
int Area::roomTransitionDelay{};

float Area::currentRoomXPosition{}, Area::currentRoomYPosition{};
float Area::previousRoomXPosition{}, Area::previousRoomYPosition{};

std::unordered_map<std::string, std::array<bool, Area::MAX_CHESTS_PER_ROOM>> Area::worldChestsLooted{};
bool Area::currentRoomChestsLooted[MAX_CHESTS_PER_ROOM]{};
bool Area::previousRoomChestsLooted[MAX_CHESTS_PER_ROOM]{};

void Area::Initialize()
{
    std::cout << "Area:: Initialize() " << std::endl;

    std::fill(std::begin(currentRoomCells), std::end(currentRoomCells), CellIndex::CELL_VOID);
    std::fill(std::begin(currentRoomFeatures), std::end(currentRoomFeatures), FeatureIndex::FEATURE_NONE);
    std::fill(std::begin(previousRoomCells), std::end(previousRoomCells), CellIndex::CELL_VOID);
    std::fill(std::begin(previousRoomFeatures), std::end(previousRoomFeatures), FeatureIndex::FEATURE_NONE);

    LoadWorldGrid("World Grid A");
    ChangeRoom(worldGridCurrentCol, worldGridCurrentRow, ROOM_TRANSITION_TELEPORT_INSTANT);
}

void Area::Uninitialize()
{
}

void Area::LoadWorldGrid(const char *worldgrid)
{
    std::cout << "Area: Loading world grid " << worldgrid << " from config/areas.cfg: " << std::endl;

    std::fill(std::begin(worldGrid), std::end(worldGrid), VOID_ROOM_ID);

    size_t x = 0;
    for (size_t y = 0; y < WORLD_GRID_ROWS; y++)
    {
        // if(y%WORLD_GRID_LAYER_ROWS == 0)
        // std::cout << std::endl;

        const char *key = std::to_string(y).c_str();
        std::string rowData = Configuration::GetString(Configuration::areasCfg, worldgrid, key);
        // std::cout << rowData;

        std::istringstream iss(rowData);
        while (std::getline(iss, rowData, ','))
        {
            if (x >= WORLD_GRID_COLS) // Invalid
            {
                // std::cout << std::endl << "Error: rowData exceeds WORLD_GRID_COLS. Discarding overflow...";
                break;
            }

            worldGrid[y * WORLD_GRID_COLS + x] = rowData;
            x++;
        }
        x = 0;

        // std::cout << std::endl;
    }

    worldGridCurrentCol = Configuration::GetInt(Configuration::areasCfg, worldgrid, "worldSpawnX");
    worldGridCurrentRow = Configuration::GetInt(Configuration::areasCfg, worldgrid, "worldSpawnY");
    std::cout << "World spawning coords = " << worldGridCurrentCol << ", " << worldGridCurrentRow << std::endl;
    std::cout << "Current room ID = " << worldGrid[worldGridCurrentRow * WORLD_GRID_COLS + worldGridCurrentCol] << std::endl;
}

void Area::LoadRoomBlueprints(int world_x, int world_y)
{
    const char *room = worldGrid[world_y * WORLD_GRID_COLS + world_x].c_str();

    std::cout << "Area: Loading room blueprint " << room << " from config/areas.cfg: " << std::endl;
    /// BEGIN CELLS PART ///
    // std::cout << "Cells BP:" << std::endl;
    std::fill(std::begin(roomCellBlueprint), std::end(roomCellBlueprint), CellIndex::BLUEPRINT_CELL_VOID_GENERIC);

    size_t col = 0;
    for (size_t row = 0; row < ROOM_ROWS; row++)
    {
        std::string keyStr = std::to_string(row) + "C";
        const char *key = keyStr.c_str();
        std::string rowData = Configuration::GetString(Configuration::areasCfg, room, key);
        // std::cout << rowData << " --> ";

        std::istringstream iss(rowData);
        while (std::getline(iss, rowData, ','))
        {
            if (col >= ROOM_COLS) // Invalid:
            {
                // std::cout << std::endl << "ERROR: rowData exceeds ROOM_COLS. Discarding overflow...";
                break;
            }

            int data = std::stoi(rowData, nullptr, 16); // String to hexedecimal conversion.
            // std::cout << std::setw(3) << data << " ";

            ParseToRoomCellBlueprint(col, row, data);
            col++;
        }
        col = 0;
        // std::cout << std::endl;
    }
    /// END CELLS PART ///
    /// BEGIN FEATURES PART ///
    // Note: literally the same thing as CELLS PART but with Feature arrays instead of Cells.
    // std::cout << "Features BP: " << std::endl;
    std::fill(std::begin(roomFeatureBlueprint), std::end(roomFeatureBlueprint), FeatureIndex::BLUEPRINT_FEATURE_NONE);

    col = 0; // reusing size_t col declared in CELLS PART.
    for (size_t row = 0; row < ROOM_ROWS; row++)
    {
        std::string keyStr = std::to_string(row) + "F";
        const char *key = keyStr.c_str();
        std::string rowData = Configuration::GetString(Configuration::areasCfg, room, key);
        // std::cout << rowData << " --> ";

        std::istringstream iss(rowData);
        while (std::getline(iss, rowData, ','))
        {
            if (col >= ROOM_COLS) // Invalid:
            {
                // std::cout << std::endl << "ERROR: rowData exceeds ROOM_COLS. Discarding overflow...";
                break;
            }

            int data = std::stoi(rowData, nullptr, 16); // String to hexedecimal conversion.
            // std::cout << std::setw(3) << data << " ";

            ParseToRoomFeatureBlueprint(col, row, data);
            col++;
        }
        col = 0;
        // std::cout << std::endl;
    }
    /// END FEATURES PART ///

    std::fill(std::begin(adjacentRooms), std::end(adjacentRooms), VOID_ROOM_ID);

    if (world_y - 1 >= 0)
        adjacentRooms[Direction::NORTH] = worldGrid[(world_y - 1) * WORLD_GRID_COLS + world_x];

    if (world_y + 1 < WORLD_GRID_ROWS)
        adjacentRooms[Direction::SOUTH] = worldGrid[(world_y + 1) * WORLD_GRID_COLS + world_x];

    if (world_x - 1 >= 0)
        adjacentRooms[Direction::WEST] = worldGrid[world_y * WORLD_GRID_COLS + (world_x - 1)];

    if (world_x + 1 < WORLD_GRID_COLS)
        adjacentRooms[Direction::EAST] = worldGrid[world_y * WORLD_GRID_COLS + (world_x + 1)];

    roomSpawnCol = Configuration::GetInt(Configuration::areasCfg, room, "spawnX");
    roomSpawnRow = Configuration::GetInt(Configuration::areasCfg, room, "spawnY");
}

void Area::ParseToRoomCellBlueprint(int x, int y, int data)
{
    if (data >= CellIndex::MARKER_BLUEPRINT_CELL_VOID_BEGIN && data <= CellIndex::MARKER_BLUEPRINT_CELL_VOID_END)
    {
        roomCellBlueprint[y * ROOM_COLS + x] = CellIndex::BLUEPRINT_CELL_VOID_GENERIC;
    }
    else if (data >= CellIndex::MARKER_BLUEPRINT_CELL_PLATFORM_BEGIN && data <= CellIndex::MARKER_BLUEPRINT_CELL_PLATFORM_END)
    {
        roomCellBlueprint[y * ROOM_COLS + x] = data;

        if (data >= CellIndex::BLUEPRINT_CELL_PLATFORM_SAME_ROOM_TELEPORT && data <= CellIndex::BLUEPRINT_CELL_PLATFORM_SAME_ROOM_TELEPORT + 15)
        {
            roomCellBlueprint[y * ROOM_COLS + x] = CellIndex::BLUEPRINT_CELL_PLATFORM_SAME_ROOM_TELEPORT;
            /// Todo: Add pair to same-level teleport destination
        }
        else if (data >= CellIndex::BLUEPRINT_CELL_PLATFORM_OTHER_ROOM_TELEPORT && data <= CellIndex::BLUEPRINT_CELL_PLATFORM_OTHER_ROOM_TELEPORT + 15)
        {
            roomCellBlueprint[y * ROOM_COLS + x] = CellIndex::BLUEPRINT_CELL_PLATFORM_OTHER_ROOM_TELEPORT;
            /// Todo: Add pair to other-level teleport destination
        }
    }
    /*
    else if(data >= 0xD0 && data <= 0xDF)
    {
        roomBlueprint[y*ROOM_COLS+x] = CellIndex::CELL_WALL;
    }
    */
    else // Invalid data
    {
        roomCellBlueprint[y * ROOM_COLS + x] = CellIndex::CELL_VOID;
    }
}

void Area::ParseToRoomFeatureBlueprint(int x, int y, int data)
{
    if (data >= FeatureIndex::BLUEPRINT_FEATURE_NONE && data < FeatureIndex::NUM_BLUEPRINT_FEATURE_TYPES)
        roomFeatureBlueprint[y * ROOM_COLS + x] = data;
    else // Invalid data
        roomFeatureBlueprint[y * ROOM_COLS + x] = FeatureIndex::FEATURE_NONE;
}

void Area::ConstructRoom()
{
    std::cout << "Area: Constructing room from blueprint: " << std::endl;
    /// BEGIN CELLS PART
    for (size_t i = 0; i < ROOM_AREA; i++)
        currentRoomCells[i] = CellIndex::CELL_VOID;

    for (size_t y = 0; y < ROOM_ROWS; y++)
    {
        for (size_t x = 0; x < ROOM_COLS; x++)
        {
            if (roomCellBlueprint[y * ROOM_COLS + x] == CellIndex::CELL_VOID)
            {
                currentRoomCells[y * ROOM_COLS + x] = CellIndex::CELL_VOID;

                // Decoration: Lower border.
                if (y > 0 && roomCellBlueprint[(y - 1) * ROOM_COLS + x] > CellIndex::MARKER_BLUEPRINT_CELL_VOID_END)
                {
                    currentRoomCells[y * ROOM_COLS + x] = CellIndex::CELL_VOID_LOWER_EDGE;
                    // Decoration: Upper-right corner. A combination of "lower border" and "right border".
                    if (x > 0 && roomCellBlueprint[y * ROOM_COLS + (x - 1)] > CellIndex::MARKER_BLUEPRINT_CELL_VOID_END)
                        currentRoomCells[y * ROOM_COLS + x] = CellIndex::CELL_VOID_UPPER_RIGHT_CORNER;
                }
                // Decoration: Right border.
                else if (x > 0 && roomCellBlueprint[y * ROOM_COLS + (x - 1)] > CellIndex::MARKER_BLUEPRINT_CELL_VOID_END)
                    currentRoomCells[y * ROOM_COLS + x] = CellIndex::CELL_VOID_RIGHT_EDGE;

                // Decoration: Lower-right corner. Note that we're looking at room here, not blueprint.
                if (x > 0 && currentRoomCells[y * ROOM_COLS + (x - 1)] == CellIndex::CELL_VOID_LOWER_EDGE &&
                    y > 0 && currentRoomCells[(y - 1) * ROOM_COLS + x] == CellIndex::CELL_VOID_RIGHT_EDGE)
                    currentRoomCells[y * ROOM_COLS + x] = CellIndex::CELL_VOID_LOWER_RIGHT_CORNER;
            }

            else if (roomCellBlueprint[y * ROOM_COLS + x] == CellIndex::BLUEPRINT_CELL_PLATFORM_BLANK)
                currentRoomCells[y * ROOM_COLS + x] = CellIndex::CELL_PLATFORM_BLANK;

            else if (roomCellBlueprint[y * ROOM_COLS + x] == CellIndex::BLUEPRINT_CELL_PLATFORM_SAME_ROOM_TELEPORT_RECEIVER_HINT)
                currentRoomCells[y * ROOM_COLS + x] = CellIndex::CELL_PLATFORM_SAME_ROOM_TELEPORT_RECEIVER_HINT;

            else if (roomCellBlueprint[y * ROOM_COLS + x] == CellIndex::BLUEPRINT_CELL_PLATFORM_OTHER_ROOM_TELEPORT_RECEIVER_HINT)
                currentRoomCells[y * ROOM_COLS + x] = CellIndex::CELL_PLATFORM_OTHER_ROOM_TELEPORT_RECEIVER_HINT;

            else if (roomCellBlueprint[y * ROOM_COLS + x] == CellIndex::BLUEPRINT_CELL_PLATFORM_SAME_ROOM_TELEPORT)
            {
                currentRoomCells[y * ROOM_COLS + x] = CellIndex::CELL_PLATFORM_SAME_ROOM_TELEPORT;
                // Todo: pair teleport destination
            }
            else if (roomCellBlueprint[y * ROOM_COLS + x] == CellIndex::BLUEPRINT_CELL_PLATFORM_OTHER_ROOM_TELEPORT)
            {
                currentRoomCells[y * ROOM_COLS + x] = CellIndex::CELL_PLATFORM_OTHER_ROOM_TELEPORT;
                // Todo: pair teleport destination
            }
            // std::cout << std::setw(2) << currentRoomCells[y * ROOM_COLS + x];
        }
        // std::cout << std::endl;
    }
    /// END CELLS PART
    /// BEGIN FEATURES PART
    for (size_t i = 0; i < ROOM_AREA; i++)
        currentRoomFeatures[i] = FeatureIndex::FEATURE_NONE;

    for (size_t y = 0; y < ROOM_ROWS; y++)
    {
        for (size_t x = 0; x < ROOM_COLS; x++)
        {
            currentRoomFeatures[y * ROOM_COLS + x] = roomFeatureBlueprint[y * ROOM_COLS + x]; /// Assuming for the time being that features and blueprints are 1:1.
        }
    }

    /// END FEATURES PART
}

void Area::UpdateRoomXYPositions()
{
    float snapshotX = currentRoomXPosition;
    float snapshotY = currentRoomYPosition;

    currentRoomXPosition = worldGridCurrentCol * ROOM_COLS * Tile::WIDTH;
    currentRoomYPosition = worldGridCurrentRow * ROOM_ROWS * Tile::HEIGHT;

    switch (roomTransitionEffect)
    {
    case ROOM_TRANSITION_ASCEND:
        previousRoomXPosition = snapshotX;
        previousRoomYPosition = currentRoomYPosition + ROOM_ROWS * Tile::HEIGHT * LAYER_SEPARATION_RATIO;
        break;

    case ROOM_TRANSITION_DESCEND:
        previousRoomXPosition = snapshotX;
        previousRoomYPosition = currentRoomYPosition - ROOM_ROWS * Tile::HEIGHT * LAYER_SEPARATION_RATIO;
        break;

    default:
        previousRoomXPosition = snapshotX;
        previousRoomYPosition = snapshotY;
        break;
    }

    Camera::SetDestination(previousRoomXPosition, previousRoomYPosition);
    Camera::WarpToXYDestination();

    Camera::SetDestination(currentRoomXPosition, currentRoomYPosition);
}

void Area::Logic()
{
    if (inRoomTransition)
    {
        if (roomTransitionEffect == ROOM_TRANSITION_TELEPORT_INSTANT)
        {
            Camera::WarpToXYDestination();
        }
        else // Not instant
        {
            if (roomTransitionDelay > 0)
                roomTransitionDelay--;

            if (roomTransitionDelay <= 0)
            {
                Camera::ApproachDestinationLinear(ROOM_TRANSITION_X_SPEED, ROOM_TRANSITION_Y_SPEED);
            }
        }

        if (Camera::atDestination)
        {
            inRoomTransition = false;
        }
    }
}

void Area::Drawing()
{
    for (size_t y = 0; y < ROOM_ROWS; y++)
    {
        for (size_t x = 0; x < ROOM_COLS; x++)
        {
            al_draw_bitmap(Image::areaCellsSub[currentRoomCells[y * ROOM_COLS + x]],
                           x * Tile::WIDTH + currentRoomXPosition - Camera::xPosition,
                           y * Tile::HEIGHT + currentRoomYPosition - Camera::yPosition,
                           0);

            if (currentRoomFeatures[y * ROOM_COLS + x] > FeatureIndex::FEATURE_NONE)
            {
                int chestNumber = currentRoomFeatures[y * ROOM_COLS + x];
                bool looted = currentRoomChestsLooted[chestNumber - FeatureIndex::MARKER_FEATURE_CHEST_BEGIN];
                if (looted)
                {
                    al_draw_bitmap(Image::areaFeaturesSub[FeatureIndex::SPRITE_CHEST_OPEN_INDEX],
                                   x * Tile::WIDTH + currentRoomXPosition - Camera::xPosition,
                                   y * Tile::HEIGHT + currentRoomYPosition - Camera::yPosition,
                                   0);
                }
                else if (!looted)
                {
                    al_draw_bitmap(Image::areaFeaturesSub[FeatureIndex::SPRITE_CHEST_CLOSED_INDEX],
                                   x * Tile::WIDTH + currentRoomXPosition - Camera::xPosition,
                                   y * Tile::HEIGHT + currentRoomYPosition - Camera::yPosition,
                                   0);
                }
            }
        }
    }

    if (inRoomTransition)
    {
        for (size_t y = 0; y < ROOM_ROWS; y++)
        {
            for (size_t x = 0; x < ROOM_COLS; x++)
            {
                al_draw_bitmap(Image::areaCellsSub[previousRoomCells[y * ROOM_COLS + x]],
                               x * Tile::WIDTH + previousRoomXPosition - Camera::xPosition,
                               y * Tile::HEIGHT + previousRoomYPosition - Camera::yPosition,
                               0);

                if (previousRoomFeatures[y * ROOM_COLS + x] > FeatureIndex::FEATURE_NONE)
                {
                    int chestNumber = previousRoomFeatures[y * ROOM_COLS + x];
                    bool looted = previousRoomChestsLooted[chestNumber - FeatureIndex::MARKER_FEATURE_CHEST_BEGIN];
                    if (looted)
                    {
                        al_draw_bitmap(Image::areaFeaturesSub[FeatureIndex::SPRITE_CHEST_OPEN_INDEX],
                                       x * Tile::WIDTH + previousRoomXPosition - Camera::xPosition,
                                       y * Tile::HEIGHT + previousRoomYPosition - Camera::yPosition,
                                       0);
                    }
                    else if (!looted)
                    {
                        al_draw_bitmap(Image::areaFeaturesSub[FeatureIndex::SPRITE_CHEST_CLOSED_INDEX],
                                       x * Tile::WIDTH + previousRoomXPosition - Camera::xPosition,
                                       y * Tile::HEIGHT + previousRoomYPosition - Camera::yPosition,
                                       0);
                    }
                }
            }
        }
    }
}

void Area::ChangeRoom(int dest_x, int dest_y, int transition_effect)
{
    if (dest_x < 0 || dest_x >= WORLD_GRID_COLS || dest_y < 0 || dest_y >= WORLD_GRID_ROWS)
    {
        std::cout << "Area: Error: Room change out of bounds on worldGrid! RoomChange(x,y) redirecting to 0,0." << std::endl;
        ChangeRoom(0, 0, ROOM_TRANSITION_TELEPORT_INSTANT);
        return;
    }

    worldGridCurrentCol = dest_x;
    worldGridCurrentRow = dest_y;

    worldRoomID = worldGrid[worldGridCurrentRow * WORLD_GRID_COLS + worldGridCurrentCol];

    std::copy(std::begin(currentRoomCells), std::end(currentRoomCells), std::begin(previousRoomCells));
    std::copy(std::begin(currentRoomFeatures), std::end(currentRoomFeatures), std::begin(previousRoomFeatures));

    previousRoomChestsLooted[0] = currentRoomChestsLooted[0];
    previousRoomChestsLooted[1] = currentRoomChestsLooted[1];
    previousRoomChestsLooted[2] = currentRoomChestsLooted[2];

    currentRoomChestsLooted[0] = worldChestsLooted[worldGrid[worldGridCurrentRow * WORLD_GRID_COLS + worldGridCurrentCol]][0];
    currentRoomChestsLooted[1] = worldChestsLooted[worldGrid[worldGridCurrentRow * WORLD_GRID_COLS + worldGridCurrentCol]][1];
    currentRoomChestsLooted[2] = worldChestsLooted[worldGrid[worldGridCurrentRow * WORLD_GRID_COLS + worldGridCurrentCol]][2];

    LoadRoomBlueprints(worldGridCurrentCol, worldGridCurrentRow);
    ConstructRoom();

    inRoomTransition = true;
    roomTransitionEffect = transition_effect;
    roomTransitionDelay = 0; // Default / fallback

    switch (roomTransitionEffect)
    {
    case ROOM_TRANSITION_TELEPORT_INSTANT:
        break;

    case ROOM_TRANSITION_TRANSLATION: // Movement to an adjacent room.
        break;

    case ROOM_TRANSITION_ASCEND:
        roomTransitionDelay = ROOM_TRANSITION_ASCEND_DELAY;
        break;

    case ROOM_TRANSITION_DESCEND:
        roomTransitionDelay = ROOM_TRANSITION_DESCEND_DELAY;
        break;

    default:
        ChangeRoom(worldGridCurrentCol, worldGridCurrentRow, ROOM_TRANSITION_TELEPORT_INSTANT); // Recursive, fallback
        std::cout << "Area: ChangeRoom(): Invalid transition effect. Fallback to ROOM_TRANSITION_TELEPORT_INSTANT." << std::endl;
        return;
        break;
    }

    UpdateRoomXYPositions();
}

bool Area::RoomBoundaryCheck(int x, int y)
{
    if (x >= 0 && x < ROOM_COLS && y >= 0 && y < ROOM_ROWS)
        return false;

    return true;
}

bool Area::WalkObstacleCheck(int x, int y)
{
    if (RoomBoundaryCheck(x, y)) // Out of bounds in the first place
        return true;

    int checkIndex = y * ROOM_COLS + x;

    // if (currentRoomCells[checkIndex] >= CellIndex::MARKER_CELL_PLATFORM_BEGIN && currentRoomCells[checkIndex] <= CellIndex::MARKER_CELL_PLATFORM_END)
    if (currentRoomFeatures[checkIndex] == FeatureIndex::FEATURE_NONE)
        return false;

    return true;
}

bool Area::VoidCellCheck(int x, int y)
{
    if (RoomBoundaryCheck(x, y)) // Out of bounds in the first place
        return false;

    int checkIndex = y * ROOM_COLS + x;

    if (currentRoomCells[checkIndex] >= CellIndex::MARKER_CELL_VOID_BEGIN && currentRoomCells[checkIndex] <= CellIndex::MARKER_CELL_VOID_END)
        return true;

    return false;
}

bool Area::TeleporterCellCheck(int x, int y)
{
    if (RoomBoundaryCheck(x, y)) // Out of bounds in the first place
        return false;

    int checkIndex = y * ROOM_COLS + x;

    if (currentRoomCells[checkIndex] >= CellIndex::MARKER_CELL_PLATFORM_TELEPORT_BEGIN && currentRoomCells[checkIndex] <= CellIndex::MARKER_CELL_PLATFORM_TELEPORT_END)
        return true;

    return false;
}

void Area::ActivateFeature(int x, int y)
{
    if (RoomBoundaryCheck(x, y)) // Out of bounds.
    {
        // Todo: question mark response.
        return; // Prevent invalid array access in the next step.
    }

    int feature = currentRoomFeatures[y * ROOM_COLS + x];

    if (feature == FeatureIndex::FEATURE_NONE)
    {
    }
    else
    {
        Dialog::Activate("Features", "chestLocked");
    }
}

void Area::AscendLayer()
{
    int worldGridSearchRow = worldGridCurrentRow;
    int searchAttempts = 0;
    bool destinationFound = false;
    while (!destinationFound)
    {
        searchAttempts++;
        if (searchAttempts > WORLD_GRID_LAYERS + 2)
        {
            // Fallback.
            std::cout << "Area:: AscendLayer() searchAttempts fallback: Redirecting to VOID_ROOM_ID" << std::endl;
            std::cout << "This isn't supposed to happen, just saying." << std::endl;
            ChangeRoom(0, 0, ROOM_TRANSITION_TELEPORT_INSTANT);
            return;
        }

        worldGridSearchRow -= WORLD_GRID_LAYER_ROWS;
        if (worldGridSearchRow < 0)
            worldGridSearchRow += WORLD_GRID_ROWS; // Prevent out of bounds search, effectively loops search back to bottom layer.

        if (worldGrid[worldGridSearchRow * WORLD_GRID_COLS + worldGridCurrentCol] != VOID_ROOM_ID)
        {
            ChangeRoom(worldGridCurrentCol, worldGridSearchRow, ROOM_TRANSITION_ASCEND);
            destinationFound = true;
            std::cout << "Area: Debug AscendLayer() searchAttempts = " << searchAttempts << std::endl;
        }
        else
        {
            std::cout << "uh, void" << std::endl;
        }
        std::cout << "Area: Debug AscendLayer()" << " search result=" << worldGrid[worldGridSearchRow * WORLD_GRID_COLS + worldGridCurrentCol] << std::endl;
    }
}

void Area::DescendLayer()
{
    int worldGridSearchRow = worldGridCurrentRow;
    int searchAttempts = 0;
    bool destinationFound = false;
    while (!destinationFound)
    {
        searchAttempts++;
        if (searchAttempts > WORLD_GRID_LAYERS + 2)
        {
            // Fallback.
            std::cout << "Area:: DescendLayer() searchAttempts fallback: Redirecting to VOID_ROOM_ID" << std::endl;
            std::cout << "This isn't supposed to happen, just saying." << std::endl;
            ChangeRoom(0, 0, ROOM_TRANSITION_TELEPORT_INSTANT); // Prevent out of bounds search, effectively loops search back to top layer.
            return;
        }

        worldGridSearchRow += WORLD_GRID_LAYER_ROWS;
        if (worldGridSearchRow >= WORLD_GRID_ROWS)
            worldGridSearchRow -= WORLD_GRID_ROWS;

        int searchIndex = worldGridSearchRow * WORLD_GRID_COLS + worldGridCurrentCol;

        if (worldGrid[searchIndex] != VOID_ROOM_ID)
        {
            destinationFound = true;
            ChangeRoom(worldGridCurrentCol, worldGridSearchRow, ROOM_TRANSITION_DESCEND);
        }
        std::cout << "Area: Debug DescendLayer() searchAttempts = " << searchAttempts << std::endl;
        std::cout << "Area: Debug DescendLayer()" << " search result=" << worldGrid[worldGridSearchRow * WORLD_GRID_COLS + worldGridCurrentCol] << std::endl;
        // std::cout << "Area: Debug DescendLayer() searchIndex = " << searchIndex << std::endl;
        std::cout << std::endl;
    }
}