#include "image.h"

ALLEGRO_BITMAP* Image::menuOptionMarkerPng;

ALLEGRO_BITMAP* Image::titleImagePng;

ALLEGRO_BITMAP* Image::settingsVolumeBarFullPng;
ALLEGRO_BITMAP* Image::settingsVolumeBarEmptyPng;

ALLEGRO_BITMAP* Image::areaCellsPng;
ALLEGRO_BITMAP* Image::areaCellsSub[CellIndex::NUM_CELL_TYPES];

ALLEGRO_BITMAP* Image::actorPng;
ALLEGRO_BITMAP* Image::actorWalkSub[ActorIndex::NUM_FACING_DIRS * ActorIndex::NUM_WALK_FRAMES];
ALLEGRO_BITMAP* Image::actorStandSub[ActorIndex::NUM_FACING_DIRS * ActorIndex::NUM_STAND_FRAMES];

void Image::Initialize()
{
    al_init_image_addon();
    al_init_primitives_addon();

    LoadResources();
}

void Image::Uninitialize()
{
    UnloadResources();

    al_shutdown_primitives_addon();
    al_shutdown_image_addon();
}

void Image::LoadResources()
{
    menuOptionMarkerPng = al_load_bitmap("menuOptionMarker.png");

    titleImagePng = al_load_bitmap("titleImage.png");

    settingsVolumeBarFullPng = al_load_bitmap("settingsVolumeBarFull.png");
    settingsVolumeBarEmptyPng = al_load_bitmap("settingsVolumeBarEmpty.png");

    areaCellsPng = al_load_bitmap("areaCells.png");
    for(size_t i = 0; i < CellIndex::NUM_CELL_TYPES; i++)
        areaCellsSub[i] = al_create_sub_bitmap(areaCellsPng, Tile::WIDTH*i, Tile::HALF_HEIGHT*0, Tile::WIDTH, Tile::HEIGHT);

    actorPng = al_load_bitmap("actorWalk.png");
    for(size_t i = 0; i < ActorIndex::NUM_STAND_FRAMES * ActorIndex::NUM_FACING_DIRS; i++)
        actorStandSub[i] = al_create_sub_bitmap(actorPng,
                                           i*ActorIndex::NUM_WALK_FRAMES*Tile::WIDTH + ActorIndex::WALK_STAND_FRAME_INDEX*Tile::WIDTH,
                                           0,
                                           Tile::WIDTH, Tile::HEIGHT);
    for(size_t i = 0; i < ActorIndex::NUM_WALK_FRAMES * ActorIndex::NUM_FACING_DIRS; i++)
        actorWalkSub[i] = al_create_sub_bitmap(actorPng,
                                               i*Tile::WIDTH,
                                               0,
                                               Tile::WIDTH, Tile::HEIGHT);


}

void Image::UnloadResources()
{
    al_destroy_bitmap(menuOptionMarkerPng);

    al_destroy_bitmap(titleImagePng);

    al_destroy_bitmap(settingsVolumeBarFullPng);
    al_destroy_bitmap(settingsVolumeBarEmptyPng);

    for(size_t i = 0; i < CellIndex::NUM_CELL_TYPES; i++)
        al_destroy_bitmap(areaCellsSub[i]);
    al_destroy_bitmap(areaCellsPng);

    for(size_t i = 0; i < ActorIndex::NUM_FACING_DIRS; i++)
        al_destroy_bitmap(actorStandSub[i]);
    for(size_t i = 0; i < ActorIndex::NUM_WALK_FRAMES * ActorIndex::NUM_FACING_DIRS; i++)
        al_destroy_bitmap(actorWalkSub[i]);
    al_destroy_bitmap(actorPng);
}

