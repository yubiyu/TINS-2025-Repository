#include "image.h"

ALLEGRO_BITMAP *Image::menuOptionMarkerPng;

ALLEGRO_BITMAP *Image::titleImagePng;

ALLEGRO_BITMAP *Image::loadgamePlaceholderPng;

ALLEGRO_BITMAP *Image::archivePlaceholderPng;

ALLEGRO_BITMAP *Image::settingsVolumeBarFullPng;
ALLEGRO_BITMAP *Image::settingsVolumeBarEmptyPng;

ALLEGRO_BITMAP *Image::areaCellsPng;
std::vector<ALLEGRO_BITMAP *> Image::areaCellsSub;

ALLEGRO_BITMAP *Image::areaFeaturesPng;
std::vector<ALLEGRO_BITMAP *> Image::areaFeaturesSub;

ALLEGRO_BITMAP *Image::actorPng;
std::vector<ALLEGRO_BITMAP *> Image::actorWalkSub;
std::vector<ALLEGRO_BITMAP *> Image::actorStandSub;

ALLEGRO_BITMAP *Image::foodPng;
std::vector<ALLEGRO_BITMAP *> Image::foodSub;

ALLEGRO_BITMAP *Image::statusFramePng;
ALLEGRO_BITMAP *Image::statusFrameMouthPng;
std::vector<ALLEGRO_BITMAP *> Image::statusFrameMouthSub;

ALLEGRO_BITMAP *Image::wingIconPng;

ALLEGRO_BITMAP *Image::dialogFramePng;
ALLEGRO_BITMAP *Image::dialogCaretPng;
ALLEGRO_BITMAP *Image::dialogCaretSub[2];

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

    loadgamePlaceholderPng = al_load_bitmap("loadMenu.png");

    archivePlaceholderPng = al_load_bitmap("archiveMenu.png");

    settingsVolumeBarFullPng = al_load_bitmap("settingsVolumeBarFull.png");
    settingsVolumeBarEmptyPng = al_load_bitmap("settingsVolumeBarEmpty.png");

    areaCellsPng = al_load_bitmap("areaCells.png");
    for (size_t i = 0; i < CellIndex::NUM_CELL_TYPES; i++)
        areaCellsSub.push_back(al_create_sub_bitmap(areaCellsPng, Tile::WIDTH * i, Tile::HEIGHT * 0, Tile::WIDTH, Tile::HEIGHT));

    areaFeaturesPng = al_load_bitmap("areaFeatures.png");
    for (size_t i = 0; i < FeatureIndex::NUM_SPRITES; i++)
        areaFeaturesSub.push_back(al_create_sub_bitmap(areaFeaturesPng, Tile::WIDTH * i, Tile::HEIGHT * 0, Tile::WIDTH, Tile::HEIGHT));

    actorPng = al_load_bitmap("actorAtlas.png");

    for (size_t y = 0; y < ActorIndex::NUM_SPRITE_IDS; y++)
    {
        for (size_t x = 0; x < Direction::NUM_DIRECTIONS * ActorIndex::NUM_WALK_FRAMES; x++)
        {
            actorWalkSub.push_back(al_create_sub_bitmap(actorPng, x * Tile::WIDTH, y * Tile::HEIGHT, Tile::WIDTH, Tile::HEIGHT));

            if (x % ActorIndex::NUM_WALK_FRAMES == ActorIndex::WALK_STAND_FRAME_INDEX)
                actorStandSub.push_back(al_create_sub_bitmap(actorPng, x * Tile::WIDTH, y * Tile::HEIGHT, Tile::WIDTH, Tile::HEIGHT));
        }
    }

    foodPng = al_load_bitmap("food.png");

    for( size_t i = 0; i < FoodIndex::NUM_FOOD_TYPES; i++)
        foodSub.push_back(al_create_sub_bitmap(foodPng, Tile::WIDTH*i, Tile::HEIGHT*0, Tile::WIDTH, Tile::HEIGHT));

    statusFramePng = al_load_bitmap("statusFrame.png");
    statusFrameMouthPng = al_load_bitmap("statusFrameMouth.png");
    for(size_t i = 0; i < StatusFrameIndex::NUM_MOUTH_FRAMES; i++)
        statusFrameMouthSub.push_back(al_create_sub_bitmap(statusFrameMouthPng, Tile::WIDTH*i, Tile::HEIGHT*0, Tile::WIDTH, Tile::HEIGHT));

    wingIconPng = al_load_bitmap("wingIcon.png");

    dialogFramePng = al_load_bitmap("dialogFrame.png");
    dialogCaretPng = al_load_bitmap("dialogCaret.png");
    dialogCaretSub[0] = al_create_sub_bitmap(dialogCaretPng, 0, 0, Tile::HALF_WIDTH, Tile::HALF_HEIGHT);
    dialogCaretSub[1] = al_create_sub_bitmap(dialogCaretPng, Tile::HALF_WIDTH, 0, Tile::HALF_WIDTH, Tile::HALF_HEIGHT);
}

void Image::UnloadResources()
{
    std::cout << "Image: Unloading resources." << std::endl;
    al_destroy_bitmap(menuOptionMarkerPng);

    al_destroy_bitmap(titleImagePng);

    al_destroy_bitmap(loadgamePlaceholderPng);

    al_destroy_bitmap(archivePlaceholderPng);

    al_destroy_bitmap(settingsVolumeBarFullPng);
    al_destroy_bitmap(settingsVolumeBarEmptyPng);

    for (size_t i = 0; i < areaCellsSub.size(); i++)
        al_destroy_bitmap(areaCellsSub[i]);
    areaCellsSub.clear();
    al_destroy_bitmap(areaCellsPng);

    for (size_t i = 0; i < areaFeaturesSub.size(); i++)
        al_destroy_bitmap(areaFeaturesSub[i]);
    areaFeaturesSub.clear();
    al_destroy_bitmap(areaFeaturesPng);

    for (size_t i = 0; i < actorStandSub.size(); i++)
        al_destroy_bitmap(actorStandSub[i]);
    actorStandSub.clear();
    for (size_t i = 0; i < actorWalkSub.size(); i++)
        al_destroy_bitmap(actorWalkSub[i]);
    actorWalkSub.clear();
    al_destroy_bitmap(actorPng);

    for(size_t i = 0; i < foodSub.size(); i++)
        al_destroy_bitmap(foodSub[i]);
    foodSub.clear();
    al_destroy_bitmap(foodPng);

    al_destroy_bitmap(statusFramePng);
    for(size_t i = 0; i < statusFrameMouthSub.size(); i++)
        al_destroy_bitmap(statusFrameMouthSub[i]);
    statusFrameMouthSub.clear();
    al_destroy_bitmap(statusFrameMouthPng);

    al_destroy_bitmap(wingIconPng);

    al_destroy_bitmap(dialogFramePng);
    al_destroy_bitmap(dialogCaretSub[0]);
    al_destroy_bitmap(dialogCaretSub[1]);
    al_destroy_bitmap(dialogCaretPng);
}
