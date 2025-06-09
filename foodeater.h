#pragma once

#include "timer.h"

#include "util.h"

#include "statusframeindex.h"

#include "dialog.h"

#include <vector>

struct FoodEater
{
    static bool hasWings; // HAX: put this somewhere else later!

    static int nutrition;
    static const int INITIAL_NUTRITION = 50;
    static const int NUTRITION_MAX = 99;
    static const int HUNGRY_THRESHOLD = 33;
    static const int NUTRITION_PER_FOOD = 20;
    static const int NUTRITION_PER_FOOD_WHEN_HUNGRY = 25;
    static bool isEating;
    static bool isHungry; // Auto eats

    static size_t maxFoodReserves;
    static const int DEFAULT_MAX_FOOD_RESERVES = 2;

    static std::vector<int>foodToEat;

    static int munchProgress; // In logic ticks.
    static const int MUNCH_DURATION = Timer::FPS*1.5;

    static int mouthIconFrame;
    static const int MUNCH_BITE_DELAY_MAX = 10;
    static constexpr float MUNCH_JITTER_OFFSET_RANDOM_RANGE = 2.0;
    static float munchDrawingYOffset;

    static void Initialize();
    static void Uninitialize();

    static void Logic();

    static void AddFood(int food_id);
    static void InitiateEating();

    static void ProgressNutrition(int iterations);

    static void AcquireWings();

};