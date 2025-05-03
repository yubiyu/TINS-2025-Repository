#pragma once

#include "core/util.h"

#include "resource/image.h"

#include "world/actorindex.h"

#include "flecs/flecs.h"

#include <iostream>

struct World
{
    static flecs::world* world;

    static void Initialize()
    {
        world = new flecs::world();
    }

    static void Uninitialize()
    {
        delete world;
    }

    static void Logic()
    {
    }
};

struct Components
{
    struct Player {};
    struct NPC {};
    struct Active {};

    struct Cell{int x, y;};
    struct Position{float x, y;};
    struct Destination{float x, y;};
    struct DrawPosition{float x, y;};
    struct Facing{int direction;};

    struct Animation
    {
        int action;
        int currentFrame, numFrames;
        int currentFrameDelay, maxFrameDelay;

        void Advance()
        {
            currentFrameDelay++;
            if(currentFrameDelay > maxFrameDelay)
            {
                currentFrameDelay = 0;
                currentFrame++;
                if(currentFrame >= numFrames)
                {
                    currentFrame = 0;
                }
            }
        }
    };

};
