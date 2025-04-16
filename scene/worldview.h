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

#include "world/camera.h"
#include "world/area.h"

#include "scene/scene.h"


struct Worldview
{

    static void Initialize();
    static void Uninitialize();

    static void Logic();
    static void Input();
    static void Drawing();

    static void ProgressWorld();
    static void UpdateUI();

    static void DrawGridUnderlay();
    static void DrawGridCameraCrosshair();
    static void DrawGridText(float mouseTransformedX, float mouseTransformedY);


};
