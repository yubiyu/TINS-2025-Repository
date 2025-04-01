#include "image.h"

ALLEGRO_BITMAP* Image::menuOptionMarkerPng;

ALLEGRO_BITMAP* Image::titleImagePng;

ALLEGRO_BITMAP* Image::settingsVolumeBarFullPng;
ALLEGRO_BITMAP* Image::settingsVolumeBarEmptyPng;

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
}

void Image::UnloadResources()
{
    al_destroy_bitmap(menuOptionMarkerPng);

    al_destroy_bitmap(titleImagePng);

    al_destroy_bitmap(settingsVolumeBarFullPng);
    al_destroy_bitmap(settingsVolumeBarEmptyPng);
}

