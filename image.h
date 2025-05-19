#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "tile.h"
#include "cellindex.h"
#include "actorindex.h"

#include <vector>
#include <iostream>

struct Image
{
    static ALLEGRO_BITMAP *scalingBuffer;

    static ALLEGRO_BITMAP *menuOptionMarkerPng;

    static ALLEGRO_BITMAP *titleImagePng;

    static ALLEGRO_BITMAP *settingsVolumeBarFullPng;
    static ALLEGRO_BITMAP *settingsVolumeBarEmptyPng;

    static ALLEGRO_BITMAP *areaCellsPng;
    static std::vector<ALLEGRO_BITMAP*>areaCellsSub;

    static ALLEGRO_BITMAP *actorPng;
    static std::vector<ALLEGRO_BITMAP*>actorWalkSub;
    static std::vector<ALLEGRO_BITMAP*>actorStandSub;

    static ALLEGRO_BITMAP *statusFramePng;

    static ALLEGRO_BITMAP *dialogFramePng;
    static ALLEGRO_BITMAP *dialogCaretPng;
    static ALLEGRO_BITMAP *dialogCaretSub[2];

    static void Initialize();
    static void Uninitialize();

    static void LoadResources();
    static void UnloadResources();
};
