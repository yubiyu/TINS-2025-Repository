#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "core/tile.h"
#include "core/util.h"

#include "input/keyboard.h"
#include "input/mouse.h"

#include "resource/image.h"
#include "resource/audio.h"
#include "resource/text.h"
#include "resource/palette.h"

#include "scene/scene.h"

#include "world/camera.h"
#include "world/area.h"
#include "world/actor.h"
#include "world/pc.h"

struct Worldview
{
    static void Initialize();
    static void Uninitialize();

    static void Logic();
    static void Input();
    static void Drawing();

    static void DrawGridUnderlay();
    static void DrawGridCameraCrosshair();
    static void DrawGridText(float mouseTransformedX, float mouseTransformedY);

};
