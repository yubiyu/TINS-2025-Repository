#include "pc.h"

PC *PC::pc = nullptr;

PC::PC()
{
    SetIsPC(true);

    SetHasAnimations(true);
    SetSpriteID(ActorIndex::SPRITE_OWL);

    SetWorldXYCell(Area::worldGridCurrentCol * Area::ROOM_COLS + Area::roomSpawnCol,
                   Area::worldGridCurrentRow * Area::ROOM_ROWS + Area::roomSpawnRow,
                   true);
}

PC::~PC()
{
}

void PC::Logic()
{
    Actor::Logic();
}

void PC::Drawing()
{
    size_t drawIndex;

    switch (GetAction())
    {
    case ActorIndex::ACTION_WALK:

        drawIndex = (GetSpriteID() * ActorIndex::WALK_SUB_BITMAPS_COLS) + GetFacing() * ActorIndex::NUM_WALK_FRAMES + GetCurrentFrame();
        al_draw_bitmap(Image::actorWalkSub[drawIndex],
                       GetXPosition() + GetDrawingXOffset() - Camera::xPosition,
                       GetYPosition() + GetDrawingYOffset() - Camera::yPosition,
                       0);
        break;

    case ActorIndex::ACTION_STAND:
        drawIndex = GetSpriteID() * ActorIndex::STAND_SUB_BITMAPS_COLS +
                    GetFacing() * ActorIndex::NUM_STAND_FRAMES;
        al_draw_bitmap(Image::actorStandSub[drawIndex],
                       GetXPosition() + GetDrawingXOffset() - Camera::xPosition,
                       GetYPosition() + GetDrawingYOffset() - Camera::yPosition,
                       0);
        break;
    }
}

void PC::Input()
{
    if (Keyboard::keyInput[Keyboard::KEY_UP])
    {
        if (!Keyboard::keyInput[Keyboard::KEY_DOWN] && !Keyboard::keyInput[Keyboard::KEY_LEFT] && !Keyboard::keyInput[Keyboard::KEY_RIGHT])
        {
            if (Keyboard::keyHoldTicks[Keyboard::KEY_UP] == 1)
                Face(Direction::UP);
            else if (Keyboard::keyHoldTicks[Keyboard::KEY_UP] > Keyboard::INPUT_TAP_TICKS_THRESHOLD)
                Walk(Direction::UP);
        }
    }

    else if (Keyboard::keyInput[Keyboard::KEY_DOWN])
    {
        if (!Keyboard::keyInput[Keyboard::KEY_UP] && !Keyboard::keyInput[Keyboard::KEY_LEFT] && !Keyboard::keyInput[Keyboard::KEY_RIGHT])
        {
            if (Keyboard::keyHoldTicks[Keyboard::KEY_DOWN] == 1)
                Face(Direction::DOWN);
            else if (Keyboard::keyHoldTicks[Keyboard::KEY_DOWN] > Keyboard::INPUT_TAP_TICKS_THRESHOLD)
                Walk(Direction::DOWN);
        }
    }

    else if (Keyboard::keyInput[Keyboard::KEY_LEFT])
    {
        if (!Keyboard::keyInput[Keyboard::KEY_UP] && !Keyboard::keyInput[Keyboard::KEY_DOWN] && !Keyboard::keyInput[Keyboard::KEY_RIGHT])
        {
            if (Keyboard::keyHoldTicks[Keyboard::KEY_LEFT] == 1)
                Face(Direction::LEFT);
            else if (Keyboard::keyHoldTicks[Keyboard::KEY_LEFT] > Keyboard::INPUT_TAP_TICKS_THRESHOLD)
                Walk(Direction::LEFT);
        }
    }

    else if (Keyboard::keyInput[Keyboard::KEY_RIGHT])
    {
        if (!Keyboard::keyInput[Keyboard::KEY_UP] && !Keyboard::keyInput[Keyboard::KEY_DOWN] && !Keyboard::keyInput[Keyboard::KEY_LEFT])
        {
            if (Keyboard::keyHoldTicks[Keyboard::KEY_RIGHT] == 1)
                Face(Direction::RIGHT);
            else if (Keyboard::keyHoldTicks[Keyboard::KEY_RIGHT] > Keyboard::INPUT_TAP_TICKS_THRESHOLD)
                Walk(Direction::RIGHT);
        }
    }
    else
    {
        if (!Keyboard::keyInput[Keyboard::KEY_UP] && !Keyboard::keyInput[Keyboard::KEY_DOWN] && !Keyboard::keyInput[Keyboard::KEY_LEFT] && !Keyboard::keyInput[Keyboard::KEY_RIGHT])
            Stand();
    }

    if (Keyboard::keyHoldTicks[Keyboard::KEY_X] == 1)
    {
        FoodEater::InitiateEating();

        if (FoodEater::hasWings && FoodEater::foodToEat.empty())
        {
            // Winning condition: Ascend from the center of sun room with wings.
            if (FoodEater::hasWings                                                                                                                 // 1. has wings
                && Area::worldGridCurrentCol == Area::WORLD_GRID_SUN_LOCATION_COL && Area::worldGridCurrentRow == Area::WORLD_GRID_SUN_LOCATION_ROW // 2. At sun room
                && GetRoomXCell() >= Area::SUN_ROOM_TARGET_COL_MIN && GetRoomXCell() <= Area::SUN_ROOM_TARGET_COL_MAX                               // 3. In the correct x range
                && GetRoomYCell() >= Area::SUN_ROOM_TARGET_ROW_MIN && GetRoomYCell() <= Area::SUN_ROOM_TARGET_ROW_MAX)                              // 4. In the correct y range
                Area::winConditionInitiated = true;

            InitiateAscendLayer();
        }
    }

    if (GetAtDestination())
    {
        if (Settings::cheatsEnabled)
        {
            if (Keyboard::keyHoldTicks[Keyboard::KEY_C] == 1)
                InitiateAscendLayer();

            if (Keyboard::keyHoldTicks[Keyboard::KEY_V] == 1)
                InitiateDescendLayer();
        }
    }
}
