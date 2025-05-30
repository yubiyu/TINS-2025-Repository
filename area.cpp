#include "area.h"

std::string Area::worldGrid[WORLD_COLS * WORLD_ROWS];
int Area::worldCurrentCol{}, Area:: worldCurrentRow{};


int Area::roomBlueprint[ROOM_COLS * ROOM_ROWS];
int Area::currentRoom[ROOM_COLS * ROOM_ROWS];
int Area::previousRoom[ROOM_COLS * ROOM_ROWS];

int Area::roomSpawnCol{}, Area::roomSpawnRow{};

std::string Area::adjacentRooms[Direction::NUM_DIRECTIONS];

bool Area::inRoomTransition{};
int Area::roomTransitionEffect{};
int Area::roomTransitionDirection{};

float Area::currentRoomXPosition{}, Area::currentRoomYPosition{};
float Area::previousRoomXPosition{}, Area::previousRoomYPosition{};

void Area::Initialize()
{
    std::fill(std::begin(currentRoom), std::end(currentRoom), CellIndex::CELL_VOID);
    std::fill(std::begin(previousRoom), std::end(previousRoom), CellIndex::CELL_VOID);

    LoadWorldGrid("World Grid A");
    LoadRoomBlueprint(worldCurrentCol, worldCurrentRow);
    ConstructRoom();
}

void Area::Uninitialize()
{
}

void Area::LoadWorldGrid(const char *worldgrid)
{
    std::cout << "Area: Loading world grid " << worldgrid << " from config/areas.cfg: " << std::endl;

    std::fill(std::begin(worldGrid), std::end(worldGrid), "0000");

    size_t x = 0;
    for(size_t y = 0; y < WORLD_ROWS; y++)
    {
        const char *key = std::to_string(y).c_str();
        std::string rowData = Configuration::GetString(Configuration::areasCfg, worldgrid, key);
        std::cout << rowData;

        std::istringstream iss(rowData);
        while(std::getline(iss, rowData, ','))
        {
            if(x >= WORLD_COLS) // Invalid
            {
                std::cout << std::endl 
                          << "Error: rowData exceeds WORLD_COLS. Discarding overflow...";
                break;
            }

            worldGrid[y*WORLD_COLS+x] = rowData;
            x++;
        }
        x = 0;
        std::cout << std::endl;
    }

    worldCurrentCol = Configuration::GetInt(Configuration::areasCfg, worldgrid, "worldSpawnX");
    worldCurrentRow = Configuration::GetInt(Configuration::areasCfg, worldgrid, "worldSpawnY");
    std::cout << "World spawning coords = " << worldCurrentCol << ", " << worldCurrentRow << std::endl;
    std::cout << "Current room ID = " << worldGrid[worldCurrentRow*WORLD_COLS + worldCurrentCol] << std::endl;

}

void Area::LoadRoomBlueprint(int world_x, int world_y)
{
    const char *room = worldGrid[world_y*WORLD_COLS+world_x].c_str();

    std::cout << "Area: Loading room blueprint " << room << " from config/areas.cfg: " << std::endl;

    std::fill(std::begin(roomBlueprint), std::end(roomBlueprint), CellIndex::BLUEPRINT_CELL_VOID_GENERIC);

    size_t col = 0;
    for (size_t row = 0; row < ROOM_ROWS; row++)
    {
        const char *key = std::to_string(row).c_str();
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

            ParseToRoomBlueprint(col, row, data);
            col++;
        }
        col = 0;
        std::cout << std::endl;
    }

    if(world_y-1 >= 0)
        adjacentRooms[Direction::NORTH] = worldGrid[(world_y-1)*WORLD_COLS + world_x];

    if(world_y+1 < WORLD_ROWS)
        adjacentRooms[Direction::SOUTH] = worldGrid[(world_y+1)*WORLD_COLS + world_x];

    if(world_x-1 >= 0)
        adjacentRooms[Direction::WEST]  = worldGrid[world_y*WORLD_COLS + (world_x-1)];

    if(world_x+1 < WORLD_COLS)
        adjacentRooms[Direction::EAST]  = worldGrid[world_y*WORLD_COLS + (world_x+1)];


    roomSpawnCol = Configuration::GetInt(Configuration::areasCfg, room, "spawnX");
    roomSpawnRow = Configuration::GetInt(Configuration::areasCfg, room, "spawnY");
}

void Area::ParseToRoomBlueprint(int x, int y, int data)
{
    if (data >= CellIndex::MARKER_BLUEPRINT_CELL_VOID_BEGIN && data <= CellIndex::MARKER_BLUEPRINT_CELL_VOID_END)
    {
        roomBlueprint[y * ROOM_COLS + x] = CellIndex::BLUEPRINT_CELL_VOID_GENERIC;
    }
    else if (data >= CellIndex::MARKER_BLUEPRINT_CELL_PLATFORM_BEGIN && data <= CellIndex::MARKER_BLUEPRINT_CELL_PLATFORM_END)
    {
        roomBlueprint[y * ROOM_COLS + x] = data;

        if (data >= CellIndex::BLUEPRINT_CELL_PLATFORM_SAME_ROOM_TELEPORT && data <= CellIndex::BLUEPRINT_CELL_PLATFORM_SAME_ROOM_TELEPORT + 15)
        {
            roomBlueprint[y * ROOM_COLS + x] = CellIndex::BLUEPRINT_CELL_PLATFORM_SAME_ROOM_TELEPORT;
            /// Todo: Add pair to same-level teleport destination
        }
        else if (data >= CellIndex::BLUEPRINT_CELL_PLATFORM_OTHER_ROOM_TELEPORT && data <= CellIndex::BLUEPRINT_CELL_PLATFORM_OTHER_ROOM_TELEPORT + 15)
        {
            roomBlueprint[y * ROOM_COLS + x] = CellIndex::BLUEPRINT_CELL_PLATFORM_OTHER_ROOM_TELEPORT;
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
        roomBlueprint[y * ROOM_COLS + x] = CellIndex::CELL_VOID;
    }
}

void Area::ConstructRoom()
{
    std::cout << "Area: Constructing room from blueprint: " << std::endl;

    for (size_t i = 0; i < ROOM_COLS * ROOM_ROWS; i++)
        currentRoom[i] = CellIndex::CELL_VOID;

    for (size_t y = 0; y < ROOM_ROWS; y++)
    {
        for (size_t x = 0; x < ROOM_COLS; x++)
        {
            if (roomBlueprint[y * ROOM_COLS + x] == CellIndex::CELL_VOID)
            {
                currentRoom[y * ROOM_COLS + x] = CellIndex::CELL_VOID;

                // Decoration: Lower border.
                if (y > 0 && roomBlueprint[(y - 1) * ROOM_COLS + x] > CellIndex::MARKER_BLUEPRINT_CELL_VOID_END)
                {
                    currentRoom[y * ROOM_COLS + x] = CellIndex::CELL_VOID_LOWER_EDGE;
                    // Decoration: Upper-right corner. A combination of "lower border" and "right border".
                    if (x > 0 && roomBlueprint[y * ROOM_COLS + (x - 1)] > CellIndex::MARKER_BLUEPRINT_CELL_VOID_END)
                        currentRoom[y * ROOM_COLS + x] = CellIndex::CELL_VOID_UPPER_RIGHT_CORNER;
                }
                // Decoration: Right border.
                else if (x > 0 && roomBlueprint[y * ROOM_COLS + (x - 1)] > CellIndex::MARKER_BLUEPRINT_CELL_VOID_END)
                    currentRoom[y * ROOM_COLS + x] = CellIndex::CELL_VOID_RIGHT_EDGE;

                // Decoration: Lower-right corner. Note that we're looking at room here, not blueprint.
                if (x > 0 && currentRoom[y * ROOM_COLS + (x - 1)] == CellIndex::CELL_VOID_LOWER_EDGE &&
                    y > 0 && currentRoom[(y - 1) * ROOM_COLS + x] == CellIndex::CELL_VOID_RIGHT_EDGE)
                    currentRoom[y * ROOM_COLS + x] = CellIndex::CELL_VOID_LOWER_RIGHT_CORNER;
            }

            else if (roomBlueprint[y * ROOM_COLS + x] == CellIndex::BLUEPRINT_CELL_PLATFORM_BLANK)
                currentRoom[y * ROOM_COLS + x] = CellIndex::CELL_PLATFORM_BLANK;

            else if (roomBlueprint[y * ROOM_COLS + x] == CellIndex::BLUEPRINT_CELL_PLATFORM_SAME_ROOM_TELEPORT_RECEIVER_HINT)
                currentRoom[y * ROOM_COLS + x] = CellIndex::CELL_PLATFORM_SAME_ROOM_TELEPORT_RECEIVER_HINT;

            else if (roomBlueprint[y * ROOM_COLS + x] == CellIndex::BLUEPRINT_CELL_PLATFORM_OTHER_ROOM_TELEPORT_RECEIVER_HINT)
                currentRoom[y * ROOM_COLS + x] = CellIndex::CELL_PLATFORM_OTHER_ROOM_TELEPORT_RECEIVER_HINT;

            else if (roomBlueprint[y * ROOM_COLS + x] == CellIndex::BLUEPRINT_CELL_PLATFORM_SAME_ROOM_TELEPORT)
            {
                currentRoom[y * ROOM_COLS + x] = CellIndex::CELL_PLATFORM_SAME_ROOM_TELEPORT;
                // Todo: pair teleport destination
            }
            else if (roomBlueprint[y * ROOM_COLS + x] == CellIndex::BLUEPRINT_CELL_PLATFORM_OTHER_ROOM_TELEPORT)
            {
                currentRoom[y * ROOM_COLS + x] = CellIndex::CELL_PLATFORM_OTHER_ROOM_TELEPORT;
                // Todo: pair teleport destination
            }
            std::cout << std::setw(2) << currentRoom[y * ROOM_COLS + x];
        }
        std::cout << std::endl;
    }
}

void Area::Logic()
{
    if (inRoomTransition)
    {
        if (roomTransitionEffect == ROOM_TRANSITION_TRANSLATION)
        {
            if (currentRoomXPosition < 0)
            {
                currentRoomXPosition += ROOM_TRANSITION_X_SPEED;
                previousRoomXPosition += ROOM_TRANSITION_X_SPEED;
            }
            else if (currentRoomXPosition > 0)
            {
                currentRoomXPosition -= ROOM_TRANSITION_X_SPEED;
                previousRoomXPosition -= ROOM_TRANSITION_X_SPEED;
            }

            if (currentRoomYPosition < 0)
            {
                currentRoomYPosition += ROOM_TRANSITION_Y_SPEED;
                previousRoomYPosition += ROOM_TRANSITION_Y_SPEED;
            }
            else if (currentRoomYPosition > 0)
            {
                currentRoomYPosition -= ROOM_TRANSITION_Y_SPEED;
                previousRoomYPosition -= ROOM_TRANSITION_Y_SPEED;
            }

            if (currentRoomXPosition == 0 && currentRoomYPosition == 0)
            {
                inRoomTransition = false;
            }
        }
        else if (roomTransitionEffect == ROOM_TRANSITION_TELEPORT_INSTANT)
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
            al_draw_bitmap(Image::areaCellsSub[currentRoom[y * ROOM_COLS + x]],
                           x * Tile::WIDTH + currentRoomXPosition, y * Tile::HEIGHT + currentRoomYPosition,
                           0);
        }
    }

    if (inRoomTransition && roomTransitionEffect == ROOM_TRANSITION_TRANSLATION)
    {
        for (size_t y = 0; y < ROOM_ROWS; y++)
        {
            for (size_t x = 0; x < ROOM_COLS; x++)
            {
                al_draw_bitmap(Image::areaCellsSub[previousRoom[y * ROOM_COLS + x]],
                               x * Tile::WIDTH + previousRoomXPosition, y * Tile::HEIGHT + previousRoomYPosition,
                               0);
            }
        }
    }
}

void Area::ChangeRoom(int dest_x, int dest_y)
{
    if(dest_x < 0 || dest_x >= WORLD_COLS || dest_y < 0 || dest_y >= WORLD_ROWS)
    {
        std::cout << "Area: Error: Room change out of bounds on worldGrid! Roomchange redirecting to 0,0." << std::endl;
        ChangeRoom(0,0);
        return;
    }

    worldCurrentCol = dest_x;
    worldCurrentRow = dest_y;

    inRoomTransition = true;

    roomTransitionEffect = ROOM_TRANSITION_TELEPORT_INSTANT;
    roomTransitionDirection = Direction::NONE;

    for (size_t i = 0; i < Direction::NUM_DIRECTIONS; i++)
    {
        if (adjacentRooms[i] == worldGrid[dest_y * WORLD_COLS + dest_x])
        {
            roomTransitionEffect = ROOM_TRANSITION_TRANSLATION;
            roomTransitionDirection = i;
            break;
        }
    }

    std::copy(std::begin(currentRoom), std::end(currentRoom), std::begin(previousRoom));
    LoadRoomBlueprint(dest_x, dest_y);
    ConstructRoom();

    previousRoomXPosition = 0;
    previousRoomYPosition = 0;
    currentRoomXPosition = 0;
    currentRoomYPosition = 0;

    switch (roomTransitionDirection)
    {
    case Direction::NORTH:
        currentRoomYPosition -= Tile::HEIGHT * ROOM_ROWS;
        break;

    case Direction::SOUTH:
        currentRoomYPosition += Tile::HEIGHT * ROOM_ROWS;
        break;

    case Direction::WEST:
        currentRoomXPosition -= Tile::WIDTH * ROOM_COLS;
        break;

    case Direction::EAST:
        currentRoomXPosition += Tile::WIDTH * ROOM_COLS;
        break;
    }
}