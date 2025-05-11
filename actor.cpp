#include "actor.h"

Actor::Actor()
{
    isActive = true;

    atDestination = true;

    facing = ActorIndex::FACING_DIR_DOWN;
    moveSpeed = ActorIndex::MOVE_SPEED_BASE;

    SetAction(ActorIndex::ACTION_STAND);
}

Actor::~Actor()
{

}

void Actor::Logic()
{
    if(!atDestination)
    {
        ApproachDestinationLinear(moveSpeed);
    }

    if(hasAnimations)
    {
        currentFrameDelay++;
        if(currentFrameDelay > maxFrameDelay)
        {
            currentFrameDelay = 0;
            currentFrame++;
            if(currentFrame >= numFrames)
            {
                currentFrame = 0;
            }
        }
    }
}

void Actor::Face(int in_dir)
{
    if(atDestination)
        facing = in_dir;
}

void Actor::Walk(int in_dir)
{
    Face(in_dir);

    if(atDestination)
    {
        atDestination = false;

        SetAction(ActorIndex::ACTION_WALK);

        switch(facing)
        {
        case ActorIndex::FACING_DIR_UP:
            SetYCell(yCell-1, false);
            break;
        case ActorIndex::FACING_DIR_DOWN:
            SetYCell(yCell+1, false);
            break;
        case ActorIndex::FACING_DIR_LEFT:
            SetXCell(xCell-1, false);
            break;
        case ActorIndex::FACING_DIR_RIGHT:
            SetXCell(xCell+1, false);
            break;
        }
    }
}

void Actor::Stand()
{
    if(atDestination)
        SetAction(ActorIndex::ACTION_STAND);
}

void Actor::ApproachDestinationLinear(float change)
{
    if(xPosition < xDestination)
        xPosition += change;
    else if(xPosition > xDestination)
        xPosition -= change;

    if(yPosition < yDestination)
        yPosition += change;
    else if(yPosition > yDestination)
        yPosition -= change;

    if(std::abs(xDestination - xPosition) <= change && std::abs(yDestination - yPosition) <= change)
    {
        WarpToXYDestination();
        atDestination = true;
    }
}

void Actor::ApproachDestinationFractional(float change)
{
    if(xPosition != xDestination)
        xPosition += (xDestination - xPosition)*change;

    if(yPosition != yDestination)
        yPosition += (yDestination - yPosition)*change;

    if(std::abs(xDestination - xPosition) <= change && std::abs(yDestination - yPosition) <= change)
    {
        WarpToXYDestination();
        atDestination = true;
    }
}

void Actor::SetAction(int which_action)
{
    if(action != which_action)
    {
        SetCurrentFrame(0);
        SetCurrentFrameDelay(0);
    }

    action = which_action;

    if(hasAnimations)
    {
        switch(action)
        {
        case ActorIndex::ACTION_WALK:
            SetNumFrames(ActorIndex::NUM_WALK_FRAMES);
            break;

        case ActorIndex::ACTION_STAND:
            SetNumFrames(ActorIndex::NUM_STAND_FRAMES);
            break;
        }
        SetMaxFrameDelay(ActorIndex::BASE_FRAME_DELAY);

    }
}
