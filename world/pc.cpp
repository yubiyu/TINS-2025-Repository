#include "world/pc.h"

PC* PC::pc;

PC::PC()
{
    SetHasAnimations(true);
    SetSpriteID(ActorIndex::SPRITE_OWL);
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

    switch(GetAction())
    {
    case ActorIndex::ACTION_WALK:
        drawIndex = (GetSpriteID()*ActorIndex::WALK_SUB_BITMAPS_COLS) + GetFacing()*ActorIndex::NUM_WALK_FRAMES + GetCurrentFrame();
        al_draw_bitmap(Image::actorWalkSub[drawIndex], GetXPosition(), GetYPosition(), 0);
        break;

    case ActorIndex::ACTION_STAND:
        drawIndex = GetSpriteID()*ActorIndex::STAND_SUB_BITMAPS_COLS +
                    GetFacing()*ActorIndex::NUM_STAND_FRAMES;
        al_draw_bitmap(Image::actorStandSub[drawIndex], GetXPosition(), GetYPosition(), 0);
        break;
    }
}

void PC::Input()
{
    if(Keyboard::keyInput[Keyboard::KEY_UP])
    {
        if(!Keyboard::keyInput[Keyboard::KEY_DOWN] && !Keyboard::keyInput[Keyboard::KEY_LEFT] && !Keyboard::keyInput[Keyboard::KEY_RIGHT] )
        {
            if(Keyboard::keyHoldTicks[Keyboard::KEY_UP] == 1)
                Face(ActorIndex::FACING_DIR_UP);
            else if(Keyboard::keyHoldTicks[Keyboard::KEY_UP] > Keyboard::INPUT_TAP_TICKS)
                Walk(ActorIndex::FACING_DIR_UP);
        }
    }

    else if(Keyboard::keyInput[Keyboard::KEY_DOWN])
    {
        if(!Keyboard::keyInput[Keyboard::KEY_UP] && !Keyboard::keyInput[Keyboard::KEY_LEFT] && !Keyboard::keyInput[Keyboard::KEY_RIGHT] )
        {
            if(Keyboard::keyHoldTicks[Keyboard::KEY_DOWN] == 1)
                Face(ActorIndex::FACING_DIR_DOWN);
            else if(Keyboard::keyHoldTicks[Keyboard::KEY_DOWN] > Keyboard::INPUT_TAP_TICKS)
                Walk(ActorIndex::FACING_DIR_DOWN);
        }
    }

    else if(Keyboard::keyInput[Keyboard::KEY_LEFT])
    {
        if(!Keyboard::keyInput[Keyboard::KEY_UP] && !Keyboard::keyInput[Keyboard::KEY_DOWN] && !Keyboard::keyInput[Keyboard::KEY_RIGHT] )
        {
            if(Keyboard::keyHoldTicks[Keyboard::KEY_LEFT] == 1)
                Face(ActorIndex::FACING_DIR_LEFT);
            else if(Keyboard::keyHoldTicks[Keyboard::KEY_LEFT] > Keyboard::INPUT_TAP_TICKS)
                Walk(ActorIndex::FACING_DIR_LEFT);
        }
    }

    else if(Keyboard::keyInput[Keyboard::KEY_RIGHT])
    {
        if(!Keyboard::keyInput[Keyboard::KEY_UP] && !Keyboard::keyInput[Keyboard::KEY_DOWN] && !Keyboard::keyInput[Keyboard::KEY_LEFT] )
        {
            if(Keyboard::keyHoldTicks[Keyboard::KEY_RIGHT] == 1)
                Face(ActorIndex::FACING_DIR_RIGHT);
            else if(Keyboard::keyHoldTicks[Keyboard::KEY_RIGHT] > Keyboard::INPUT_TAP_TICKS)
                Walk(ActorIndex::FACING_DIR_RIGHT);
        }
    }
    else
    {
        if(!Keyboard::keyInput[Keyboard::KEY_UP] && !Keyboard::keyInput[Keyboard::KEY_DOWN] && !Keyboard::keyInput[Keyboard::KEY_LEFT] && !Keyboard::keyInput[Keyboard::KEY_RIGHT])
            Stand();

    }

}
