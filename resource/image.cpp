#include "image.h"

ALLEGRO_BITMAP* Image::menuOptionMarkerPng;

ALLEGRO_BITMAP* Image::titleImagePng;

ALLEGRO_BITMAP* Image::settingsVolumeBarFullPng;
ALLEGRO_BITMAP* Image::settingsVolumeBarEmptyPng;

ALLEGRO_BITMAP* Image::areaCellsPng;
std::vector<ALLEGRO_BITMAP*> Image::areaCellsSub;

ALLEGRO_BITMAP* Image::actorPng;
std::vector<ALLEGRO_BITMAP*> Image::actorWalkSub;
std::vector<ALLEGRO_BITMAP*> Image::actorStandSub;


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
    std::cout << "Image: Loading resources." << std::endl;

    menuOptionMarkerPng = al_load_bitmap("menuOptionMarker.png");

    titleImagePng = al_load_bitmap("titleImage.png");

    settingsVolumeBarFullPng = al_load_bitmap("settingsVolumeBarFull.png");
    settingsVolumeBarEmptyPng = al_load_bitmap("settingsVolumeBarEmpty.png");

    areaCellsPng = al_load_bitmap("areaCells.png");
    for(size_t i = 0; i < CellIndex::NUM_CELL_TYPES; i++)
        areaCellsSub.push_back( al_create_sub_bitmap(areaCellsPng, Tile::WIDTH*i, Tile::HALF_HEIGHT*0, Tile::WIDTH, Tile::HEIGHT) );

    actorPng = al_load_bitmap("actorAtlas.png");

    for(size_t y = 0; y < ActorIndex::NUM_SPRITE_IDS; y++)
    {
        for(size_t x = 0; x < ActorIndex::NUM_FACING_DIRS*ActorIndex::NUM_WALK_FRAMES; x++)
        {
            actorWalkSub.push_back( al_create_sub_bitmap(actorPng, x*Tile::WIDTH, y*Tile::HEIGHT, Tile::WIDTH, Tile::HEIGHT) );

            if(x % (ActorIndex::NUM_WALK_FRAMES + ActorIndex::WALK_STAND_FRAME_INDEX) == 0)
                actorStandSub.push_back( al_create_sub_bitmap(actorPng, x*Tile::WIDTH, y*Tile::HEIGHT, Tile::WIDTH, Tile::HEIGHT) );

        }
    }
}

void Image::UnloadResources()
{
    al_destroy_bitmap(menuOptionMarkerPng);

    al_destroy_bitmap(titleImagePng);

    al_destroy_bitmap(settingsVolumeBarFullPng);
    al_destroy_bitmap(settingsVolumeBarEmptyPng);

    for(size_t i = 0; i < areaCellsSub.size(); i++)
        al_destroy_bitmap(areaCellsSub[i]);
    areaCellsSub.clear();
    al_destroy_bitmap(areaCellsPng);

    for(size_t i = 0; i < actorStandSub.size(); i++)
        al_destroy_bitmap(actorStandSub[i]);
    actorStandSub.clear();
    for(size_t i = 0; i < actorWalkSub.size(); i++)
        al_destroy_bitmap(actorWalkSub[i]);
    actorWalkSub.clear();
    al_destroy_bitmap(actorPng);
}
