#include "statusframe.h"

void StatusFrame::Initialize()
{
}

void StatusFrame::Uninitialize()
{
}

void StatusFrame::Logic()
{
    if (PC::pc != nullptr)
    {
    }
}

void StatusFrame::Drawing()
{
    al_draw_bitmap(Image::statusFramePng, FRAME_X_POSITION, FRAME_Y_POSITION, 0);

    if(FoodEater::isEating)
    {
        al_draw_bitmap(Image::statusFrameMouthSub[FoodEater::mouthIconFrame], FRAME_X_POSITION + ICON_MOUTH_X_POSITION, FRAME_Y_POSITION, 0);
    }
    else
        al_draw_bitmap(Image::statusFrameMouthSub[0], FRAME_X_POSITION + ICON_MOUTH_X_POSITION, FRAME_Y_POSITION, 0);

    size_t foodPosition = 0;
    for(std::vector<int>::iterator it = FoodEater::foodToEat.begin(); it != FoodEater::foodToEat.end(); ++it)
    {
        if(foodPosition == 0 && FoodEater::isEating)
        {
          al_draw_bitmap(Image::foodSub[(*it)], 
          FRAME_X_POSITION + FOOD_ICONS_X_POSITION + Tile::WIDTH*foodPosition,
          FRAME_Y_POSITION + FoodEater::munchDrawingYOffset, 
          0);
        }
        else
          al_draw_bitmap(Image::foodSub[(*it)], 
          FRAME_X_POSITION + FOOD_ICONS_X_POSITION + Tile::WIDTH*foodPosition,
          FRAME_Y_POSITION,
          0);

        foodPosition++;
    }

    if(FoodEater::hasWings)
        al_draw_bitmap(Image::wingIconPng, FRAME_X_POSITION + ICON_WINGS_X_POSITION, FRAME_Y_POSITION, 0);

    if(FoodEater::isHungry)
    {
        Util::string_al_draw_text(FONTDEF_STATUS_FRAME, COLKEY_STATUS_FRAME_TEXT_ALERT,
                              FRAME_X_POSITION + TEXT_FOODEATER_NUTRITION_X_POSITION,
                              FRAME_Y_POSITION + TEXT_Y_POSITION,
                              ALLEGRO_ALIGN_RIGHT, std::to_string(FoodEater::nutrition));
    }
    else
    Util::string_al_draw_text(FONTDEF_STATUS_FRAME, COLKEY_STATUS_FRAME_TEXT,
                              FRAME_X_POSITION + TEXT_FOODEATER_NUTRITION_X_POSITION,
                              FRAME_Y_POSITION + TEXT_Y_POSITION,
                              ALLEGRO_ALIGN_RIGHT, std::to_string(FoodEater::nutrition));

    std::ostringstream chestsLootedOSS;
    chestsLootedOSS << std::setw(2) << std::setfill('0') << Area::chestsLootedCount;
    Util::string_al_draw_text(FONTDEF_STATUS_FRAME, COLKEY_STATUS_FRAME_TEXT,
                              FRAME_X_POSITION + TEXT_AREA_CHESTS_LOOTED_X_POSITION,
                              FRAME_Y_POSITION + TEXT_Y_POSITION,
                              ALLEGRO_ALIGN_LEFT, chestsLootedOSS.str());


}

void StatusFrame::Input()
{
}