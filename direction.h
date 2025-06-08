#pragma once

struct Direction
{

    static const int NONE = -1; // Not counted as one of four directions. Definitely should not be used as an array index.

    enum enumDirection
    {
        RIGHT = 0,
        UP = 1,
        LEFT = 2,
        DOWN = 3
    };

    enum enumCompass
    {
        EAST = 0,
        NORTH = 1,
        WEST = 2,
        SOUTH = 3
    };

    static const int MARKER_DIRECTIONS_END = EAST;
    static const int NUM_DIRECTIONS = 4;
};