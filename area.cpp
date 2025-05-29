#include "area.h"

int Area::roomBlueprint[COLS * ROWS];
int Area::currentRoom[COLS * ROWS];
int Area::previousRoom[COLS * ROWS];

int Area::defaultSpawnCol{}, Area::defaultSpawnRow{};

std::string Area::adjacentRooms[Direction::NUM_DIRECTIONS];

bool Area::inRoomTransition{};
int Area::roomTransitionEffect{};
int Area::roomTransitionDirection{};

float Area::currentRoomXPosition{}, Area::currentRoomYPosition{};
float Area::previousRoomXPosition{}, Area::previousRoomYPosition{};

void Area::Initialize(const char *room)
{
    std::fill(std::begin(currentRoom), std::end(currentRoom), CellIndex::CELL_VOID);
    std::fill(std::begin(previousRoom), std::end(previousRoom), CellIndex::CELL_VOID);

    LoadRoomBlueprint(room);
    ConstructRoom();
}

void Area::Uninitialize()
{
}

void Area::LoadRoomBlueprint(const char *room)
{
    std::cout << "Area: Loading room blueprint " << room << " from config/areas: " << std::endl;

    std::fill(std::begin(roomBlueprint), std::end(roomBlueprint), CellIndex::BLUEPRINT_CELL_VOID_GENERIC);

    size_t x = 0;
    for (size_t y = 0; y < ROWS; y++)
    {
        const char *key = std::to_string(y).c_str();
        std::string rowData = Configuration::GetString(Configuration::areasCfg, room, key);
        std::cout << rowData << " --> ";

        std::istringstream iss(rowData);
        while (std::getline(iss, rowData, ','))
        {
            if (x >= COLS) // Invalid:
            {
                std::cout << std::endl
                          << "ERROR: rowData exceeds ROWS. Discarding overflow...";
                break;
            }

            int data = std::stoi(rowData, nullptr, 16);
            std::cout << std::setw(3) << data << " ";

            ParseToRoomBlueprint(x, y, data);
            x++;
        }
        x = 0;
        std::cout << std::endl;
    }

    if (al_get_config_value(Configuration::areasCfg, room, "roomToNorth") != NULL)
        adjacentRooms[Direction::NORTH] = Configuration::GetString(Configuration::areasCfg, room, "roomToNorth");

    if (al_get_config_value(Configuration::areasCfg, room, "roomToSouth") != NULL)
        adjacentRooms[Direction::SOUTH] = Configuration::GetString(Configuration::areasCfg, room, "roomToSouth");

    if (al_get_config_value(Configuration::areasCfg, room, "roomToWest") != NULL)
        adjacentRooms[Direction::WEST] = Configuration::GetString(Configuration::areasCfg, room, "roomToWest");

    if (al_get_config_value(Configuration::areasCfg, room, "roomToEast") != NULL)
        adjacentRooms[Direction::EAST] = Configuration::GetString(Configuration::areasCfg, room, "roomToEast");

    defaultSpawnCol = Configuration::GetInt(Configuration::areasCfg, room, "spawnX");
    defaultSpawnRow = Configuration::GetInt(Configuration::areasCfg, room, "spawnY");
}

void Area::ParseToRoomBlueprint(int x, int y, int data)
{
    if (data >= CellIndex::MARKER_BLUEPRINT_CELL_VOID_BEGIN && data <= CellIndex::MARKER_BLUEPRINT_CELL_VOID_END)
    {
        roomBlueprint[y * COLS + x] = CellIndex::BLUEPRINT_CELL_VOID_GENERIC;
    }
    else if (data >= CellIndex::MARKER_BLUEPRINT_CELL_PLATFORM_BEGIN && data <= CellIndex::MARKER_BLUEPRINT_CELL_PLATFORM_END)
    {
        roomBlueprint[y * COLS + x] = data;

        if (data >= CellIndex::BLUEPRINT_CELL_PLATFORM_SAME_ROOM_TELEPORT && data <= CellIndex::BLUEPRINT_CELL_PLATFORM_SAME_ROOM_TELEPORT + 15)
        {
            roomBlueprint[y * COLS + x] = CellIndex::BLUEPRINT_CELL_PLATFORM_SAME_ROOM_TELEPORT;
            /// Todo: Add pair to same-level teleport destination
        }
        else if (data >= CellIndex::BLUEPRINT_CELL_PLATFORM_OTHER_ROOM_TELEPORT && data <= CellIndex::BLUEPRINT_CELL_PLATFORM_OTHER_ROOM_TELEPORT + 15)
        {
            roomBlueprint[y * COLS + x] = CellIndex::BLUEPRINT_CELL_PLATFORM_OTHER_ROOM_TELEPORT;
            /// Todo: Add pair to other-level teleport destination
        }
    }
    /*
    else if(data >= 0xD0 && data <= 0xDF)
    {
        roomBlueprint[y*COLS+x] = CellIndex::CELL_WALL;
    }
    */
    else // Invalid data
    {
        roomBlueprint[y * COLS + x] = CellIndex::CELL_VOID;
    }
}

void Area::ConstructRoom()
{
    std::cout << "Area: Constructing room from blueprint: " << std::endl;

    for (size_t i = 0; i < COLS * ROWS; i++)
        currentRoom[i] = CellIndex::CELL_VOID;

    for (size_t y = 0; y < ROWS; y++)
    {
        for (size_t x = 0; x < COLS; x++)
        {
            if (roomBlueprint[y * COLS + x] == CellIndex::CELL_VOID)
            {
                currentRoom[y * COLS + x] = CellIndex::CELL_VOID;

                // Decoration: Lower border.
                if (y > 0 && roomBlueprint[(y - 1) * COLS + x] > CellIndex::MARKER_BLUEPRINT_CELL_VOID_END)
                {
                    currentRoom[y * COLS + x] = CellIndex::CELL_VOID_LOWER_EDGE;
                    // Decoration: Upper-right corner. A combination of "lower border" and "right border".
                    if (x > 0 && roomBlueprint[y * COLS + (x - 1)] > CellIndex::MARKER_BLUEPRINT_CELL_VOID_END)
                        currentRoom[y * COLS + x] = CellIndex::CELL_VOID_UPPER_RIGHT_CORNER;
                }
                // Decoration: Right border.
                else if (x > 0 && roomBlueprint[y * COLS + (x - 1)] > CellIndex::MARKER_BLUEPRINT_CELL_VOID_END)
                    currentRoom[y * COLS + x] = CellIndex::CELL_VOID_RIGHT_EDGE;

                // Decoration: Lower-right corner. Note that we're looking at room here, not blueprint.
                if (x > 0 && currentRoom[y * COLS + (x - 1)] == CellIndex::CELL_VOID_LOWER_EDGE &&
                    y > 0 && currentRoom[(y - 1) * COLS + x] == CellIndex::CELL_VOID_RIGHT_EDGE)
                    currentRoom[y * COLS + x] = CellIndex::CELL_VOID_LOWER_RIGHT_CORNER;
            }

            else if (roomBlueprint[y * COLS + x] == CellIndex::BLUEPRINT_CELL_PLATFORM_BLANK)
                currentRoom[y * COLS + x] = CellIndex::CELL_PLATFORM_BLANK;

            else if (roomBlueprint[y * COLS + x] == CellIndex::BLUEPRINT_CELL_PLATFORM_SAME_ROOM_TELEPORT_RECEIVER_HINT)
                currentRoom[y * COLS + x] = CellIndex::CELL_PLATFORM_SAME_ROOM_TELEPORT_RECEIVER_HINT;

            else if (roomBlueprint[y * COLS + x] == CellIndex::BLUEPRINT_CELL_PLATFORM_OTHER_ROOM_TELEPORT_RECEIVER_HINT)
                currentRoom[y * COLS + x] = CellIndex::CELL_PLATFORM_OTHER_ROOM_TELEPORT_RECEIVER_HINT;

            else if (roomBlueprint[y * COLS + x] == CellIndex::BLUEPRINT_CELL_PLATFORM_SAME_ROOM_TELEPORT)
            {
                currentRoom[y * COLS + x] = CellIndex::CELL_PLATFORM_SAME_ROOM_TELEPORT;
                // Todo: pair teleport destination
            }
            else if (roomBlueprint[y * COLS + x] == CellIndex::BLUEPRINT_CELL_PLATFORM_OTHER_ROOM_TELEPORT)
            {
                currentRoom[y * COLS + x] = CellIndex::CELL_PLATFORM_OTHER_ROOM_TELEPORT;
                // Todo: pair teleport destination
            }
            std::cout << std::setw(2) << currentRoom[y * COLS + x];
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
    for (size_t y = 0; y < ROWS; y++)
    {
        for (size_t x = 0; x < COLS; x++)
        {
            al_draw_bitmap(Image::areaCellsSub[currentRoom[y * COLS + x]],
                           x * Tile::WIDTH + currentRoomXPosition, y * Tile::HEIGHT + currentRoomYPosition,
                           0);
        }
    }

    if (inRoomTransition && roomTransitionEffect == ROOM_TRANSITION_TRANSLATION)
    {
        for (size_t y = 0; y < ROWS; y++)
        {
            for (size_t x = 0; x < COLS; x++)
            {
                al_draw_bitmap(Image::areaCellsSub[previousRoom[y * COLS + x]],
                               x * Tile::WIDTH + previousRoomXPosition, y * Tile::HEIGHT + previousRoomYPosition,
                               0);
            }
        }
    }
}

void Area::ChangeRoom(std::string destination)
{
    inRoomTransition = true;

    roomTransitionEffect = ROOM_TRANSITION_TELEPORT_INSTANT;
    roomTransitionDirection = Direction::NONE;

    for (size_t i = 0; i < Direction::NUM_DIRECTIONS; i++)
    {
        if (adjacentRooms[i] == destination)
        {
            roomTransitionEffect = ROOM_TRANSITION_TRANSLATION;
            roomTransitionDirection = i;
            break;
        }
    }

    std::copy(std::begin(currentRoom), std::end(currentRoom), std::begin(previousRoom));
    LoadRoomBlueprint(destination.c_str());
    ConstructRoom();

    previousRoomXPosition = 0;
    previousRoomYPosition = 0;
    currentRoomXPosition = 0;
    currentRoomYPosition = 0;

    switch (roomTransitionDirection)
    {
    case Direction::NORTH:
        currentRoomYPosition -= Tile::HEIGHT * ROWS;
        break;

    case Direction::SOUTH:
        currentRoomYPosition += Tile::HEIGHT * ROWS;
        break;

    case Direction::WEST:
        currentRoomXPosition -= Tile::WIDTH * COLS;
        break;

    case Direction::EAST:
        currentRoomXPosition += Tile::WIDTH * COLS;
        break;
    }
}