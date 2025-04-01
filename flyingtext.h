#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "camera.h"

#include "image.h"
#include "text.h"

#include "palette.h"

#include "util.h"

class FlyingText
{
public:
    bool active;
    bool queued; // Queued text does not gain distanceFlown while queued.

    bool hasIcon;
    int itemIcon;

    std::string text;

    const float scrollUpSpeed = 0.2;
    const float scrollUpXDisplacement = Tile::WIDTH*0.5;
    const float scrollUpYDisplacement = Tile::HEIGHT*(-1.5);
    const float scrollDownSpeed = 0.2;
    const float scrollDownXDisplacement = Tile::WIDTH*(-1.5);
    const float scrollDownYDisplacement = Tile::HEIGHT*(-2.5);

    bool scrollUp;
    float worldviewXPosition, worldviewYPosition;

    const int distanceFlownLimit = Tile::HEIGHT*1;
    int distanceFlown;

    FlyingText(int ic, std::string t, float x, float y, bool up);
    ~FlyingText();

    void Progress();
    void DrawOnWorldview();

};
