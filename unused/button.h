#pragma once

//#include "buttonindex.h"

#include "font.h"

#include "hax.h"

#include <allegro5/allegro_primitives.h>

#include <iostream>

class Button
{
    float frameXPosition, frameYPosition;
    float xPosition, yPosition;               // Position relative to its frame.
    float width, height;

    int identity; // Which preset to load. Also an int to be returned, to identify the button pushed.

    std::string name;

public:
    Button(){}
    ~Button(){}

    void Initialize(float frame_x, float frame_y, float x, float y, float w, float h, int id);
    void Drawing(float frame_x, float frame_y);

    bool CheckWithinButton(float x_2, float y_2, float w_2, float h_2);
    int GetIdentity() const {return identity;}


};
