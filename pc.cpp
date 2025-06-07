#include "pc.h"

PC *PC::pc = nullptr;

PC::PC()
{
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

    if (Area::inRoomTransition && Area::roomTransitionEffect == Area::ROOM_TRANSITION_ASCEND)
    {
        ascensionSpinFrameDelay++;
        if (ascensionSpinFrameDelay >= ASCENSION_SPIN_MAX_FRAME_DELAY)
        {
            ascensionSpinFrameDelay = 0;
            ascensionSpinFrame++;
            if (ascensionSpinFrame >= Direction::NUM_DIRECTIONS)
                ascensionSpinFrame = 0;
        }

        facingWithAscensionSpin = GetFacing() + ascensionSpinFrame;
        if (facingWithAscensionSpin >= Direction::NUM_DIRECTIONS)
            facingWithAscensionSpin %= Direction::NUM_DIRECTIONS;
    }
}

void PC::Drawing()
{
    size_t drawIndex;

    switch (GetAction())
    {
    case ActorIndex::ACTION_WALK:

        if (Area::inRoomTransition && Area::roomTransitionDelay > 0 && Area::roomTransitionEffect == Area::ROOM_TRANSITION_ASCEND)
        {
                // Use facingWithAscensionSpin.
                drawIndex = (GetSpriteID() * ActorIndex::WALK_SUB_BITMAPS_COLS) + facingWithAscensionSpin * ActorIndex::NUM_WALK_FRAMES + GetCurrentFrame();
                al_draw_bitmap(Image::actorWalkSub[drawIndex],
                               GetXPosition() - Camera::xPosition,
                               GetPreviousRoomYPosition() - Camera::yPosition,
                               0);
        }
        else
        {
            drawIndex = (GetSpriteID() * ActorIndex::WALK_SUB_BITMAPS_COLS) + GetFacing() * ActorIndex::NUM_WALK_FRAMES + GetCurrentFrame();
            al_draw_bitmap(Image::actorWalkSub[drawIndex],
                           GetXPosition() - Camera::xPosition,
                           GetYPosition() - Camera::yPosition,
                           0);
        }
        break;

    case ActorIndex::ACTION_STAND:

        if (Area::inRoomTransition && Area::roomTransitionDelay > 0 && Area::roomTransitionEffect == Area::ROOM_TRANSITION_ASCEND)
        {
                // Use facingWithAscensionSpin.
                drawIndex = GetSpriteID() * ActorIndex::STAND_SUB_BITMAPS_COLS +
                            facingWithAscensionSpin * ActorIndex::NUM_STAND_FRAMES;

                al_draw_bitmap(Image::actorStandSub[drawIndex],
                               GetXPosition() - Camera::xPosition,
                               GetPreviousRoomYPosition() - Camera::yPosition,
                               0);

        }
        else
        {
            drawIndex = GetSpriteID() * ActorIndex::STAND_SUB_BITMAPS_COLS +
                        GetFacing() * ActorIndex::NUM_STAND_FRAMES;
            al_draw_bitmap(Image::actorStandSub[drawIndex],
                           GetXPosition() - Camera::xPosition,
                           GetYPosition() - Camera::yPosition,
                           0);
        }
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

    /// Debug features
    if (GetAtDestination())
    {
        if (Keyboard::keyHoldTicks[Keyboard::KEY_C] == 1)
        {
            AscendLayer();
        }
        if (Keyboard::keyHoldTicks[Keyboard::KEY_V] == 1)
        {
            DescendLayer();
        }
    }
}
