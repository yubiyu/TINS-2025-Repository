#include "area.h"

std::string Area::worldGrid[WORLD_COLS * WORLD_ROWS];
int Area::worldGridCurrentCol{}, Area::worldGridCurrentRow{};

int Area::roomCellBlueprint[ROOM_AREA];
int Area::roomFeatureBlueprint[ROOM_AREA];
int Area::currentRoomCells[ROOM_AREA];
int Area::currentRoomFeatures[ROOM_AREA];
int Area::previousRoomCells[ROOM_AREA];
int Area::previousRoomFeatures[ROOM_AREA];

int Area::roomSpawnCol{}, Area::roomSpawnRow{};

std::string Area::adjacentRooms[Direction::NUM_DIRECTIONS];

bool Area::inRoomTransition{};
int Area::roomTransitionEffect{};
int Area::roomTransitionDirection{};

float Area::currentRoomXPosition{}, Area::currentRoomYPosition{};
float Area::previousRoomXPosition{}, Area::previousRoomYPosition{};

void Area::Initialize()
{
    std::fill(std::begin(currentRoomCells), std::end(currentRoomCells), CellIndex::CELL_VOID);
    std::fill(std::begin(currentRoomFeatures), std::end(currentRoomFeatures), FeatureIndex::FEATURE_NONE);

    std::fill(std::begin(previousRoomCells), std::end(previousRoomCells), CellIndex::CELL_VOID);
    std::fill(std::begin(previousRoomFeatures), std::end(previousRoomFeatures), FeatureIndex::FEATURE_NONE);

    LoadWorldGrid("World Grid A");
    LoadRoomBlueprints(worldGridCurrentCol, worldGridCurrentRow);
    ConstructRoom();

    UpdateRoomXYPositions();
    inRoomTransition = true;
    roomTransitionEffect = ROOM_TRANSITION_TELEPORT_INSTANT;
}

void Area::Uninitialize()
{
}

void Area::LoadWorldGrid(const char *worldgrid)
{
    std::cout << "Area: Loading world grid " << worldgrid << " from config/areas.cfg: " << std::endl;

    std::fill(std::begin(worldGrid), std::end(worldGrid), VOID_ROOM);

    size_t x = 0;
    for (size_t y = 0; y < WORLD_ROWS; y++)
    {
        const char *key = std::to_string(y).c_str();
        std::string rowData = Configuration::GetString(Configuration::areasCfg, worldgrid, key);
        std::cout << rowData;

        std::istringstream iss(rowData);
        while (std::getline(iss, rowData, ','))
        {
            if (x >= WORLD_COLS) // Invalid
            {
                std::cout << std::endl
                          << "Error: rowData exceeds WORLD_COLS. Discarding overflow...";
                break;
            }

            worldGrid[y * WORLD_COLS + x] = rowData;
            x++;
        }
        x = 0;
        std::cout << std::endl;
    }

    worldGridCurrentCol = Configuration::GetInt(Configuration::areasCfg, worldgrid, "worldSpawnX");
    worldGridCurrentRow = Configuration::GetInt(Configuration::areasCfg, worldgrid, "worldSpawnY");
    std::cout << "World spawning coords = " << worldGridCurrentCol << ", " << worldGridCurrentRow << std::endl;
    std::cout << "Current room ID = " << worldGrid[worldGridCurrentRow * WORLD_COLS + worldGridCurrentCol] << std::endl;
}

void Area::LoadRoomBlueprints(int world_x, int world_y)
{
    const char *room = worldGrid[world_y * WORLD_COLS + world_x].c_str();

    std::cout << "Area: Loading room blueprint " << room << " from config/areas.cfg: " << std::endl;
/// BEGIN CELLS PART ///
    std::cout << "Cells BP:" << std::endl;
    std::fill(std::begin(roomCellBlueprint), std::end(roomCellBlueprint), CellIndex::BLUEPRINT_CELL_VOID_GENERIC);

    size_t col = 0;
    for (size_t row = 0; row < ROOM_ROWS; row++)
    {
        std::string keyStr = std::to_string(row) + "C";
        const char *key = keyStr.c_str();
        std::string rowData = Configuration::GetString(Configuration::areasCfg, room, key);
        std::cout << rowData << " --> ";

        std::istringstream iss(rowData);
        while (std::getline(iss, rowData, ','))
        {
            if (col >= ROOM_COLS) // Invalid:
            {
                std::cout << std::endl
                          << "ERROR: rowData exceeds ROOM_COLS. Discarding overflow...";
                break;
            }

            int data = std::stoi(rowData, nullptr, 16); // String to hexedecimal conversion.
            std::cout << std::setw(3) << data << " ";

            ParseToRoomCellBlueprint(col, row, data);
            col++;
        }
        col = 0;
        std::cout << std::endl;
    }
/// END CELLS PART ///
/// BEGIN FEATURES PART ///
    // Note: literally the same thing as CELLS PART but with Feature arrays instead of Cells.
    std::cout << "Features BP: " << std::endl;
    std::fill(std::begin(roomFeatureBlueprint), std::end(roomFeatureBlueprint), FeatureIndex::BLUEPRINT_FEATURE_NONE);

    col = 0; // reusing size_t col declared in CELLS PART.
    for( size_t row = 0; row < ROOM_ROWS; row++)
    {
        std::string keyStr = std::to_string(row) + "F";
        const char *key = keyStr.c_str();
        std::string rowData = Configuration::GetString(Configuration::areasCfg, room, key);
        std::cout << rowData << " --> ";

        std::istringstream iss(rowData);
        while(std::getline(iss, rowData, ','))
        {
            if(col >= ROOM_COLS) // Invalid:
            {
                std::cout << std::endl 
                          << "ERROR: rowData exceeds ROOM_COLS. Discarding overflow...";
                break;
            }

            int data = std::stoi(rowData, nullptr, 16);  // String to hexedecimal conversion.
            std::cout << std::setw(3) << data << " ";

            ParseToRoomFeatureBlueprint(col, row, data);
            col++;
        }
        col = 0;
        std::cout << std::endl;
    }
/// END FEATURES PART ///

    std::fill(std::begin(adjacentRooms), std::end(adjacentRooms), VOID_ROOM);

    if (world_y - 1 >= 0)
        adjacentRooms[Direction::NORTH] = worldGrid[(world_y - 1) * WORLD_COLS + world_x];

    if (world_y + 1 < WORLD_ROWS)
        adjacentRooms[Direction::SOUTH] = worldGrid[(world_y + 1) * WORLD_COLS + world_x];

    if (world_x - 1 >= 0)
        adjacentRooms[Direction::WEST] = worldGrid[world_y * WORLD_COLS + (world_x - 1)];

    if (world_x + 1 < WORLD_COLS)
        adjacentRooms[Direction::EAST] = worldGrid[world_y * WORLD_COLS + (world_x + 1)];

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
    if(data >= FeatureIndex::BLUEPRINT_FEATURE_NONE && data < FeatureIndex::NUM_BLUEPRINT_FEATURE_TYPES)
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
            std::cout << std::setw(2) << currentRoomCells[y * ROOM_COLS + x];
        }
        std::cout << std::endl;
    }
/// END CELLS PART
/// BEGIN FEATURES PART
    for(size_t i = 0; i < ROOM_AREA; i++)
        currentRoomFeatures[i] = FeatureIndex::FEATURE_NONE;

    for(size_t y = 0; y < ROOM_ROWS; y++)
    {
        for(size_t x = 0; x < ROOM_COLS; x++)
        {
            currentRoomFeatures[y*ROOM_COLS+x] = roomFeatureBlueprint[y*ROOM_COLS+x]; /// Assuming for the time being that features and blueprints are 1:1.
        }
    }

/// END FEATURES PART
}

void Area::UpdateRoomXYPositions()
{
    previousRoomXPosition = currentRoomXPosition;
    previousRoomYPosition = currentRoomYPosition;
    currentRoomXPosition = worldGridCurrentCol * ROOM_COLS * Tile::WIDTH;
    currentRoomYPosition = worldGridCurrentRow * ROOM_ROWS * Tile::HEIGHT;

    Camera::SetDestination(currentRoomXPosition, currentRoomYPosition);
}

void Area::Logic()
{
    if (inRoomTransition)
    {
        if (roomTransitionEffect == ROOM_TRANSITION_TRANSLATION)
        {
            Camera::ApproachDestinationLinear(ROOM_TRANSITION_X_SPEED, ROOM_TRANSITION_Y_SPEED);
            if (Camera::atDestination)
                inRoomTransition = false;
        }
        else if (roomTransitionEffect == ROOM_TRANSITION_TELEPORT_INSTANT)
        {
            Camera::SetDestination(currentRoomXPosition, currentRoomYPosition);
            Camera::WarpToXYDestination();
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
                al_draw_bitmap(Image::areaFeaturesSub[currentRoomFeatures[y * ROOM_COLS + x]],
                               x * Tile::WIDTH + currentRoomXPosition - Camera::xPosition,
                               y * Tile::HEIGHT + currentRoomYPosition - Camera::yPosition,
                               0);
        }
    }

    if (inRoomTransition && roomTransitionEffect == ROOM_TRANSITION_TRANSLATION)
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
                    al_draw_bitmap(Image::areaFeaturesSub[previousRoomFeatures[y * ROOM_COLS + x]],
                                   x * Tile::WIDTH + previousRoomXPosition - Camera::xPosition,
                                   y * Tile::HEIGHT + previousRoomYPosition - Camera::yPosition,
                                   0);
            }
        }
    }
}

void Area::ChangeRoom(int dest_x, int dest_y)
{
    if (dest_x < 0 || dest_x >= WORLD_COLS || dest_y < 0 || dest_y >= WORLD_ROWS)
    {
        std::cout << "Area: Error: Room change out of bounds on worldGrid! RoomChange(x,y) redirecting to 0,0." << std::endl;
        ChangeRoom(0, 0);
        return;
    }

    worldGridCurrentCol = dest_x;
    worldGridCurrentRow = dest_y;

    UpdateRoomXYPositions();

    inRoomTransition = true;

    roomTransitionEffect = ROOM_TRANSITION_TELEPORT_INSTANT; // Default / fallback
    roomTransitionDirection = Direction::NONE;               // Default / fallback

    for (size_t i = 0; i < Direction::NUM_DIRECTIONS; i++)
    {
        if (adjacentRooms[i] == worldGrid[dest_y * WORLD_COLS + dest_x])
        {
            roomTransitionEffect = ROOM_TRANSITION_TRANSLATION;
            roomTransitionDirection = i;
            break;
        }
    }

    std::copy(std::begin(currentRoomCells), std::end(currentRoomCells), std::begin(previousRoomCells));
    std::copy(std::begin(currentRoomFeatures), std::end(currentRoomFeatures), std::begin(previousRoomFeatures));
    LoadRoomBlueprints(dest_x, dest_y);
    ConstructRoom();
}