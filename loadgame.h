#pragma once

#include "keyboard.h"

#include "image.h"

#include "scene.h"

struct LoadGame
{
    static void Initialize();
    static void Uninitialize();

    static void Logic();
    static void Input();
    static void Drawing();

};