#include "area.h"

int Area::roomBlueprint[COLS*ROWS];
int Area::room[COLS*ROWS];

int Area::defaultSpawnCol, Area::defaultSpawnRow;

void Area::Initialize(const char* room)
{
    LoadRoomBlueprint(room);
    ConstructRoom();
}

void Area::Uninitialize()
{

}

void Area::LoadRoomBlueprint(const char* room)
{
    std::cout << "Area: Loading room blueprint " << room << " from config/areas: " << std::endl;

    for(size_t i = 0; i < ROWS*COLS; i++)
        roomBlueprint[i] = CellIndex::CELL_VOID;

    size_t x = 0;
    for(size_t y = 0; y < ROWS; y++)
    {
        const char*key = std::to_string(y).c_str();
        std::string rowData = Configuration::GetString(Configuration::areasCfg, room, key);
        std::cout << rowData << " --> ";

        std::istringstream iss(rowData);
        while(std::getline(iss, rowData, ','))
        {
            if(x >= COLS) // Invalid:
            {
                std::cout << std::endl << "ERROR: rowData exceeds ROWS. Discarding overflow...";
                break;
            }

            int data = std::stoi(rowData, nullptr, 16);
            std::cout << std::setw(3) << data << " ";

            ParseToRoomBlueprint(x,y,data);
            x++;
        }
        x = 0;
        std::cout << std::endl;
    }


    defaultSpawnCol = Configuration::GetInt(Configuration::areasCfg, room, "spawnX");
    defaultSpawnRow = Configuration::GetInt(Configuration::areasCfg, room, "spawnY");
}

void Area::ParseToRoomBlueprint(int x, int y, int data)
{
    if(data >= CellIndex::MARKER_BLUEPRINT_CELL_VOID_BEGIN && data <= CellIndex::MARKER_BLUEPRINT_CELL_VOID_END)
    {
        roomBlueprint[y*COLS+x] = CellIndex::BLUEPRINT_CELL_VOID_GENERIC;
    }
    else if(data >= CellIndex::MARKER_BLUEPRINT_CELL_PLATFORM_BEGIN && data <= CellIndex::MARKER_BLUEPRINT_CELL_PLATFORM_END)
    {
        roomBlueprint[y*COLS+x] = data;
        
        if(data >= CellIndex::BLUEPRINT_CELL_PLATFORM_SAME_ROOM_TELEPORT && data <= CellIndex::BLUEPRINT_CELL_PLATFORM_SAME_ROOM_TELEPORT + 15)
        {
            roomBlueprint[y*COLS+x] = CellIndex::BLUEPRINT_CELL_PLATFORM_SAME_ROOM_TELEPORT;
            /// Todo: Add pair to same-level teleport destination
        }
        else if(data >= CellIndex::BLUEPRINT_CELL_PLATFORM_OTHER_ROOM_TELEPORT && data <= CellIndex::BLUEPRINT_CELL_PLATFORM_OTHER_ROOM_TELEPORT + 15)
        {
            roomBlueprint[y*COLS+x] = CellIndex::BLUEPRINT_CELL_PLATFORM_OTHER_ROOM_TELEPORT;
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
        roomBlueprint[y*COLS+x] = CellIndex::CELL_VOID;
    }
}

void Area::ConstructRoom()
{
    std::cout << "Area: Constructing room from blueprint: " << std::endl;

    for(size_t i = 0; i < COLS*ROWS; i++)
        room[i] = CellIndex::CELL_VOID;

    for(size_t y = 0; y < ROWS; y++)
    {
        for(size_t x = 0; x < COLS; x++)
        {
            if(roomBlueprint[y*COLS+x] == CellIndex::CELL_VOID)
            {
                room[y*COLS+x] = CellIndex::CELL_VOID;

                // Decoration: Lower border.
                if(y > 0 && roomBlueprint[(y-1)*COLS+x] > CellIndex::MARKER_BLUEPRINT_CELL_VOID_END)
                {
                    room[y*COLS+x] = CellIndex::CELL_VOID_LOWER_EDGE;
                    // Decoration: Upper-right corner. A combination of "lower border" and "right border".
                    if(x > 0 && roomBlueprint[y*COLS+(x-1)] > CellIndex::MARKER_BLUEPRINT_CELL_VOID_END)
                        room[y*COLS+x] = CellIndex::CELL_VOID_UPPER_RIGHT_CORNER;

                }
                // Decoration: Right border.
                else if(x > 0 && roomBlueprint[y*COLS+(x-1)] > CellIndex::MARKER_BLUEPRINT_CELL_VOID_END)
                    room[y*COLS+x] = CellIndex::CELL_VOID_RIGHT_EDGE;

                // Decoration: Lower-right corner. Note that we're looking at room here, not blueprint.
                if(x > 0 && room[y*COLS+(x-1)] == CellIndex::CELL_VOID_LOWER_EDGE &&
                   y > 0 && room[(y-1)*COLS+x] == CellIndex::CELL_VOID_RIGHT_EDGE)
                    room[y*COLS+x] = CellIndex::CELL_VOID_LOWER_RIGHT_CORNER;
            }

            else if(roomBlueprint[y*COLS+x] == CellIndex::BLUEPRINT_CELL_PLATFORM_BLANK)
                room[y*COLS+x] = CellIndex::CELL_PLATFORM_BLANK;

            else if(roomBlueprint[y*COLS+x] == CellIndex::BLUEPRINT_CELL_PLATFORM_SAME_ROOM_TELEPORT_RECEIVER_HINT)
                room[y*COLS+x] = CellIndex::CELL_PLATFORM_SAME_ROOM_TELEPORT_RECEIVER_HINT;

            else if (roomBlueprint[y*COLS+x] == CellIndex::BLUEPRINT_CELL_PLATFORM_OTHER_ROOM_TELEPORT_RECEIVER_HINT)
                room[y*COLS+x] = CellIndex::CELL_PLATFORM_OTHER_ROOM_TELEPORT_RECEIVER_HINT;
            
            else if(roomBlueprint[y*COLS+x] == CellIndex::BLUEPRINT_CELL_PLATFORM_SAME_ROOM_TELEPORT)
            {
                room[y*COLS+x] = CellIndex::CELL_PLATFORM_SAME_ROOM_TELEPORT;
                // Todo: pair teleport destination
            }
            else if(roomBlueprint[y*COLS+x] == CellIndex::BLUEPRINT_CELL_PLATFORM_OTHER_ROOM_TELEPORT)
            {
                room[y*COLS+x] = CellIndex::CELL_PLATFORM_OTHER_ROOM_TELEPORT;
                // Todo: pair teleport destination
            }
            std::cout << std::setw(2) << room[y*COLS+x];

        }
        std::cout << std::endl;
    }


}

void Area::Drawing()
{
    for(size_t y = 0; y < ROWS; y++)
    {
        for(size_t x = 0; x < COLS; x++)
        {
            al_draw_bitmap(Image::areaCellsSub[ room[y*COLS+x] ],
                           x*Tile::WIDTH, y*Tile::HEIGHT,
                           0);
        }
    }
}
