#pragma once

struct CellIndex
{
    enum enumCells
    {
        CELL_VOID = 0, // Default
        CELL_VOID_LOWER_EDGE = 1, // Void immediately under a platform
        CELL_VOID_RIGHT_EDGE = 2, // Void immediately right of a platform
        CELL_VOID_UPPER_RIGHT_CORNER = 3, // Void immediately under a platform AND immediately right of a platform.
        CELL_VOID_LOWER_RIGHT_CORNER = 4, // Void to the right of a LOWER_EDGE and below a RIGHT_EDGE (and of course, not a platform)

        CELL_PLATFORM = 5,
        CELL_PLATFORM_DEFAULT_SPAWN = 6,
        CELL_PLATFORM_SAME_ROOM_TELEPORT = 7,
        CELL_PLATFORM_OTHER_ROOM_TELEPORT = 8
    };
    static const int MARKER_CELL_VOID_BEGIN = CELL_VOID;
    static const int MARKER_CELL_VOID_END = CELL_VOID_LOWER_RIGHT_CORNER;
    static const int MARKER_CELL_PLATFORM_BEGIN = CELL_PLATFORM;
    static const int MARKER_CELL_PLATFORM_END = CELL_PLATFORM_OTHER_ROOM_TELEPORT;
    static const int NUM_CELL_TYPES = MARKER_CELL_PLATFORM_END + 1;

    enum enumBlueprintCells
    {
        BLUEPRINT_CELL_VOID_GENERIC = 0x00,
        BLUEPRINT_CELL_PLATFORM_GENERIC = 0x10,
        BLUEPRINT_CELL_PLATFORM_DEFAULT_SPAWN = 0xA0,
        BLUEPRINT_CELL_PLATFORM_SAME_ROOM_TELEPORT = 0xB0,
        BLUEPRINT_CELL_PLATFORM_OTHER_ROOM_TELEPORT = 0xC0
    };
    static const int MARKER_BLUEPRINT_CELL_VOID_BEGIN = BLUEPRINT_CELL_VOID_GENERIC;
    static const int MARKER_BLUEPRINT_CELL_VOID_END = BLUEPRINT_CELL_VOID_GENERIC;
    static const int MARKER_BLUEPRINT_CELL_PLATFORM_BEGIN = BLUEPRINT_CELL_PLATFORM_GENERIC;
    static const int MARKER_BLUEPRINT_CELL_PLATFORM_END = BLUEPRINT_CELL_PLATFORM_OTHER_ROOM_TELEPORT + 15;
};
