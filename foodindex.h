#pragma once


#include <map>
#include <string>

struct FoodIndex
{
    enum foodTypes
    {
        TYPE_JERKY = 0,
        TYPE_PORKCHOP = 1,
        TYPE_RIB = 2,
        TYPE_HAM = 3
    };

    static const int NUM_FOOD_TYPES = TYPE_HAM + 1;

    static inline const std::map<int, std::string> foodNames =
    {
        {TYPE_JERKY,    "Jerky"},
        {TYPE_PORKCHOP, "Porkchop"},
        {TYPE_RIB,      "Rib"},
        {TYPE_HAM,      "Ham"}
    };

};