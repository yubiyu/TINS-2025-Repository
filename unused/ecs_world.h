#pragma once

#include "flecs/flecs.h"
#include <iostream>

struct CellXY
{
    int x;
    int y;
};

struct ECSWorld
{
    static flecs::world* world;

    static flecs::entity pc;

    static void Initialize()
    {
        world = new flecs::world();
        world->component<CellXY>();

        pc = world->entity("Player");

        pc.add<CellXY>();

        pc.set<CellXY>({4,4});

        const CellXY *xy = pc.get<CellXY>();

        std::cout << "Test pc.get<CellXY>() << " << xy->x << ", " << xy->y << std::endl;

    }
    static void Uninitialize()
    {
        pc.destruct();
        delete world;
        world = nullptr;
    }
};
