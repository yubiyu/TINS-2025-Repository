#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "tile.h"

#include <vector>

struct Image
{
    static ALLEGRO_BITMAP *menuOptionMarkerPng;

    static ALLEGRO_BITMAP *titleImagePng;

    static ALLEGRO_BITMAP *settingsVolumeBarFullPng;
    static ALLEGRO_BITMAP *settingsVolumeBarEmptyPng;


    static void Initialize();
    static void Uninitialize();

    static void LoadResources();
    static void UnloadResources();
};
