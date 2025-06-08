#pragma once

#include "timer.h"

#include "util.h"

#include <vector>

struct FoodEater
{
    static int nutrition;
    static const int INITIAL_NUTRITION = 30;
    static const int NUTRITION_MAX = 99;
    static const int HUNGRY_THRESHOLD = 20;
    static const int NUTRITION_PER_FOOD = 25;
    static const int NUTRITION_PER_FOOD_WHEN_HUNGRY = 30;
    static bool isEating;
    static bool isHungry; // Auto eats

    static const int MAX_FOOD_RESERVES = 2;

    static std::vector<int>foodToEat;

    static int munchProgress; // In logic ticks.
    static const int MUNCH_DURATION = Timer::FPS*2.5;

    static const int MUNCH_BITE_DELAY_MAX = 10;
    static constexpr float MUNCH_JITTER_OFFSET_RANDOM_RANGE = 2.0;
    static float munchDrawingYOffset;

    static void Initialize();
    static void Uninitialize();

    static void Logic();

    static void AddFood(int food_id);
    static void InitiateEating();

    static void ProgressNutrition();

};