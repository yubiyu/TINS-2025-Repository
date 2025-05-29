#pragma once

struct Direction
{

    static const int NONE = -1; // Not counted as one of four directions. Definitely should not be used as an array index.

    enum enumUDLR
    {
        UP = 0,
        DOWN = 1,
        LEFT = 2,
        RIGHT = 3
    };

    enum enumCompass
    {
        NORTH = 0,
        SOUTH = 1,
        WEST = 2,
        EAST = 3
    };

    static const int MARKER_DIRECTIONS_END = EAST;
    static const int NUM_DIRECTIONS = 4;
};