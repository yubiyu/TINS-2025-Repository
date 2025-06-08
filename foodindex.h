#pragma once

#include <map>
#include <string>

struct FoodIndex
{
    enum foodTypes
    {
        TYPE_CHERRIES = 0,
        TYPE_PEAR = 1,
        TYPE_BANANA = 2,
        TYPE_ORANGE = 3,
        TYPE_PEACH = 4,
        TYPE_BERRIES = 5
    };

    static const int NUM_FOOD_TYPES = TYPE_BERRIES + 1;

    static inline const std::map<int, std::string> foodText =
    {
        {TYPE_CHERRIES, "some sweet CHERRIES!"},
        {TYPE_PEAR,     "a crispy PEAR!"},
        {TYPE_BANANA,   "some ripe BANANAS!"},
        {TYPE_ORANGE,   "an shiny ORANGE!"},
        {TYPE_PEACH,    "a tasty PEACH!"},
        {TYPE_BERRIES,  "some juicy BERRIES!"}
    };

};