#pragma once

#include "input/keyboard.h"

#include "resource/image.h"

#include "world/actorindex.h"
#include "world/actor.h"


class PC : public Actor
{

public:
    static PC* pc;

    PC()
    {
        SetHasAnimations(true);
    }
    ~PC()
    {

    }

    void Logic()
    {
        Actor::Logic();
    }

    void Drawing()
    {
        switch(GetAction())
        {
        case ActorIndex::ACTION_WALK:
            al_draw_bitmap(Image::actorWalkSub[GetFacing()*ActorIndex::NUM_WALK_FRAMES + GetCurrentFrame()], GetXPosition(), GetYPosition(), 0);
            break;

        case ActorIndex::ACTION_STAND:
            al_draw_bitmap(Image::actorStandSub[GetFacing()], GetXPosition(), GetYPosition(), 0);
            break;
        }
    }

    void Input()
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
};
