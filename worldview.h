#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "tile.h"
#include "util.h"

#include "keyboard.h"
#include "mouse.h"

#include "image.h"
#include "audio.h"
#include "text.h"
#include "palette.h"

#include "scene.h"

#include "camera.h"
#include "area.h"
#include "actor.h"
#include "pc.h"
#include "dialog.h"

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
