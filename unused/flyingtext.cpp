#include "flyingtext.h"

FlyingText::FlyingText(int ic, std::string t, float x, float y, bool up)
{
    active = true;
    queued = true;

    distanceFlown = 0;

    hasIcon = true;
    itemIcon = ic;
    text = t;
    scrollUp = up;

    if(scrollUp)
    {
        worldviewXPosition = x + scrollUpXDisplacement;
        worldviewYPosition = y + scrollUpYDisplacement;
    }
    else
    {
        worldviewXPosition = x + scrollDownXDisplacement;
        worldviewYPosition = y + scrollDownYDisplacement;
    }

    //std::cout << "Item #" << ic << " " << t << " " << x << "/" << y << std::endl;

}

FlyingText::~FlyingText()
{
    //std::cout << "Deletion test" << std::endl;
}

void FlyingText::Progress()
{
    if(!queued)
    {
        distanceFlown++;
        if(distanceFlown >= distanceFlownLimit)
        {
            active = false;
        }
        if(scrollUp)
            worldviewYPosition -= scrollUpSpeed;
        else
            worldviewYPosition += scrollDownSpeed;
    }

}

void FlyingText::DrawOnWorldview()
{
    if(!queued)
    {
        float drawX = worldviewXPosition - Camera::xPosition;
        float drawY = worldviewYPosition - Camera::yPosition;

        /*
        al_draw_bitmap_region(Image::miniCargoPng,
                              itemIcon*Tile::MINI_WIDTH, 0,
                              Tile::MINI_WIDTH, Tile::MINI_HEIGHT,
                              drawX,
                              drawY,
                              0);
                              */

        if(scrollUp)
            Util::string_al_draw_text(Text::builtin8,COLKEY_TEXT_VALUE,drawX+Tile::HALF_WIDTH,drawY,ALLEGRO_ALIGN_LEFT,text);
        else //scroll down
            Util::string_al_draw_text(Text::builtin8,COLKEY_TEXT_VALUE,drawX+Tile::HALF_WIDTH,drawY,ALLEGRO_ALIGN_LEFT,text);
    }
}
