#pragma once

/// I think we should revert to Image, but maintain a vector of ALLEGRO_BITMAP pointers to delete at the end.

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <unordered_map> // Hashes are faster than trees.
#include <vector>

#include "tile.h"

#include <iostream>

class Sprite
{
    size_t identity;
    std::string fileName;

    ALLEGRO_BITMAP* spriteSheet;
    std::unordered_map<size_t, std::vector<ALLEGRO_BITMAP*>>frames;

    int frameWidth, frameHeight;

    size_t numAnimations; // Sprite sheet rows.
    size_t numFrames; // Sprite sheet columns.

    Sprite(){}
    ~Sprite(){}

public:
    static std::unordered_map<size_t, Sprite*>sprites;

    static void Initialize();
    static void Uninitialize();

    static void Load(size_t id, const char* filename_, size_t num_animations, size_t num_frames, int frame_width, int frame_height);
    static void Unload(size_t id);

    void Draw(size_t animation, size_t frame, float x, float y)
    {
        al_draw_bitmap(frames[animation][frame], x, y, 0);
    }

    enum enumSpriteDirectory
    {
        SPRITE_TEST_A,
        SPRITE_TEST_B
    };
    static const size_t NUM_SPRITES = 2;

};
