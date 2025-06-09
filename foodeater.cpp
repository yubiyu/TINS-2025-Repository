#include "foodeater.h"

bool FoodEater::hasWings{};

int FoodEater::nutrition{};
bool FoodEater::isEating{};
bool FoodEater::isHungry{};

size_t FoodEater::maxFoodReserves{};

std::vector<int> FoodEater::foodToEat{};

int FoodEater::munchProgress{};

int FoodEater::mouthIconFrame{};

float FoodEater::munchDrawingYOffset{};

void FoodEater::Initialize()
{
    nutrition = INITIAL_NUTRITION;
    isEating = false;
    isHungry = false;

    maxFoodReserves = DEFAULT_MAX_FOOD_RESERVES;

    foodToEat.clear();

    munchProgress = 0;
    mouthIconFrame = 0;
    munchDrawingYOffset = 0;
}

void FoodEater::Uninitialize()
{
    foodToEat.clear();
}

void FoodEater::Logic()
{
    if (foodToEat.size() > 0)
    {
        if (isHungry)
            isEating = true;

        if (isEating)
        {
            if (munchProgress % MUNCH_BITE_DELAY_MAX == 0)
            {
                mouthIconFrame++;
                if (mouthIconFrame >= StatusFrameIndex::NUM_MOUTH_FRAMES)
                    mouthIconFrame = 0;

                munchDrawingYOffset = Util::RandFloatRange(-MUNCH_JITTER_OFFSET_RANDOM_RANGE, MUNCH_JITTER_OFFSET_RANDOM_RANGE);

                // Audio: Play bite sound?
            }
            if(!Dialog::isActive)
                munchProgress++;
        }

        if (foodToEat.size() > maxFoodReserves)
            munchProgress = MUNCH_DURATION + 1; // Debug: Insta-eat!

        if (munchProgress > MUNCH_DURATION)
        {
            munchProgress = 0;
            isEating = false;
            foodToEat.erase(foodToEat.begin());
            nutrition += NUTRITION_PER_FOOD;
            if (nutrition > NUTRITION_MAX)
                nutrition = NUTRITION_MAX;

            if (nutrition > HUNGRY_THRESHOLD)
                isHungry = false;
        }
    }
}

void FoodEater::AddFood(int food_id)
{
    foodToEat.push_back(food_id);
}

void FoodEater::InitiateEating()
{
    if (foodToEat.size() > 0)
        isEating = true;
}

void FoodEater::ProgressNutrition(int iterations)
{
    for (int i = 0; i < iterations; i++)
    {
        nutrition--;

        if (nutrition < 0)
            nutrition = 0;

        if (nutrition < HUNGRY_THRESHOLD)
            isHungry = true;
        else
            isHungry = false;
    }
}

void FoodEater::AcquireWings()
{
    hasWings = true;
    maxFoodReserves = 1;
}