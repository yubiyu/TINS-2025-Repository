#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "core/tile.h"
#include "world/cellindex.h"
#include "world/actorindex.h"

struct Image
{
    static ALLEGRO_BITMAP *scalingBuffer;

    static ALLEGRO_BITMAP *menuOptionMarkerPng;

    static ALLEGRO_BITMAP *titleImagePng;

    static ALLEGRO_BITMAP *settingsVolumeBarFullPng;
    static ALLEGRO_BITMAP *settingsVolumeBarEmptyPng;

    static ALLEGRO_BITMAP *areaCellsPng;
    static ALLEGRO_BITMAP *areaCellsSub[CellIndex::NUM_CELL_TYPES];

    static ALLEGRO_BITMAP *actorPng;
    static ALLEGRO_BITMAP *actorWalkSub[ActorIndex::NUM_FACING_DIRS * ActorIndex::NUM_WALK_FRAMES];
    static ALLEGRO_BITMAP *actorStandSub[ActorIndex::NUM_FACING_DIRS * ActorIndex::NUM_STAND_FRAMES];

    static void Initialize();
    static void Uninitialize();

    static void LoadResources();
    static void UnloadResources();
};
