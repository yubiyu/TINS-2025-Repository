#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "keyboard.h"
#include "mouse.h"

#include "image.h"
#include "text.h"
#include "audio.h"

#include "tile.h"
#include "camera.h"
#include "palette.h"

#include "scene.h"

#include "util.h"

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
