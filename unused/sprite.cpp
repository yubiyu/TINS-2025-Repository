#include "sprite.h"

std::unordered_map<size_t, Sprite*>Sprite::sprites;

void Sprite::Initialize()
{
    al_init_image_addon();
    al_init_primitives_addon();

    Load(SPRITE_TEST_A, "testA.png", 2, 2, Tile::WIDTH, Tile::HEIGHT);
    Load(SPRITE_TEST_B, "testB.png", 2, 2, Tile::WIDTH, Tile::HEIGHT);
}

void Sprite::Uninitialize()
{
    for(size_t i = 0; i < NUM_SPRITES; i++)
        Unload(i);

    al_shutdown_primitives_addon();
    al_shutdown_image_addon();
}

void Sprite::Load(size_t id, const char* file_name, size_t num_animations, size_t num_frames, int frame_width, int frame_height)
{
    Sprite* sprite = new Sprite();
    sprites[id] = sprite;

    sprite->identity = id;
    sprite->fileName = file_name;

    sprite->numAnimations = num_animations;
    sprite->numFrames = num_frames;
    sprite->frameWidth = frame_width;
    sprite->frameHeight = frame_height;

    sprite->spriteSheet = al_load_bitmap(sprite->fileName.c_str());
    if(sprite->spriteSheet == NULL)
        assert(sprite->fileName.c_str() && "Failed to load.");

    std::cout << sprite->fileName << " loaded with " << sprite->numAnimations << " animations " << std::endl;

    for(size_t y = 0; y <= sprite->numAnimations; y++)
    {
        for(size_t x = 0; x <= sprite->numFrames; x++)
        {
            ALLEGRO_BITMAP* frame = al_create_sub_bitmap(sprite->spriteSheet, x*sprite->frameWidth, y*sprite->frameHeight,
                                                         sprite->frameWidth, sprite->frameHeight);
            sprite->frames[y].push_back(frame);
        }
    }
}

void Sprite::Unload(size_t id)
{
    std::cout << "Deleting " << sprites[id]->fileName << "." << std::endl;
    for(std::unordered_map<size_t, std::vector<ALLEGRO_BITMAP*>>::iterator it = sprites[id]->frames.begin(); it != sprites[id]->frames.end();)
    {
        for(std::vector<ALLEGRO_BITMAP*>::iterator jt = (*it).second.begin(); jt != (*it).second.end(); jt++)
            al_destroy_bitmap(*jt);

        it = sprites[id]->frames.erase(it);
    }
    al_destroy_bitmap(sprites[id]->spriteSheet);
    delete sprites[id];
    sprites.erase(id);

}
