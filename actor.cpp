#include "actor.h"

Actor::Actor()
{
    isActive = true;

    atDestination = true;

    facing = Direction::DOWN;
    moveSpeed = ActorIndex::WALK_SPEED_BASE;

    SetAction(ActorIndex::ACTION_STAND);
}

Actor::~Actor()
{
}

void Actor::Logic()
{
    if (!atDestination)
    {
        ApproachDestinationLinear(moveSpeed);
    }

    if (hasAnimations)
    {
        currentFrameDelay++;
        if (currentFrameDelay > maxFrameDelay)
        {
            currentFrameDelay = 0;
            currentFrame++;
            if (currentFrame >= numFrames)
            {
                currentFrame = 0;
            }
        }
    }
}

void Actor::Face(int in_dir)
{
    if (atDestination)
        facing = in_dir;
}

void Actor::Walk(int in_dir)
{
    Face(in_dir);

    if (atDestination)
    {
        atDestination = false;

        SetAction(ActorIndex::ACTION_WALK);

        switch (facing)
        {
        case Direction::UP:
            if (roomYCell > 0)
                SetRoomYCell(roomYCell - 1, false);
            else if (Area::adjacentRooms[Direction::UP] != Area::VOID_ROOM)
            {
                /// Todo: Ensure only PC actor can trigger a room change.
                Area::ChangeRoom(Area::worldGridCurrentCol, Area::worldGridCurrentRow - 1);
                SetWorldYCell(worldYCell - 1, true);
            }
            break;

        case Direction::DOWN:
            if (roomYCell < Area::ROOM_ROWS - 1)
                SetRoomYCell(roomYCell + 1, false);
            else if (Area::adjacentRooms[Direction::DOWN] != Area::VOID_ROOM)
            {
                Area::ChangeRoom(Area::worldGridCurrentCol, Area::worldGridCurrentRow + 1);
                SetWorldYCell(worldYCell + 1, true);
            }
            break;

        case Direction::LEFT:
            if (roomXCell > 0)
                SetRoomXCell(roomXCell - 1, false);
            else if (Area::adjacentRooms[Direction::LEFT] != Area::VOID_ROOM)
            {
                Area::ChangeRoom(Area::worldGridCurrentCol - 1, Area::worldGridCurrentRow);
                SetWorldXCell(worldXCell - 1, true);
            }
            break;

        case Direction::RIGHT:
            if (roomXCell < Area::ROOM_COLS - 1)
                SetRoomXCell(roomXCell + 1, false);
            else if (Area::adjacentRooms[Direction::RIGHT] != Area::VOID_ROOM)
            {
                Area::ChangeRoom(Area::worldGridCurrentCol + 1, Area::worldGridCurrentRow);
                SetWorldXCell(worldXCell + 1, true);
            }
            break;
        }
    }
}

void Actor::Stand()
{
    if (atDestination)
        SetAction(ActorIndex::ACTION_STAND);
}

void Actor::ApproachDestinationLinear(float change)
{
    if (xPosition < xDestination)
        xPosition += change;
    else if (xPosition > xDestination)
        xPosition -= change;

    if (yPosition < yDestination)
        yPosition += change;
    else if (yPosition > yDestination)
        yPosition -= change;

    if (std::abs(xDestination - xPosition) <= change && std::abs(yDestination - yPosition) <= change)
    {
        WarpToXYDestination();
        atDestination = true;
    }
}

void Actor::ApproachDestinationFractional(float change)
{
    if (xPosition != xDestination)
        xPosition += (xDestination - xPosition) * change;

    if (yPosition != yDestination)
        yPosition += (yDestination - yPosition) * change;

    if (std::abs(xDestination - xPosition) <= change && std::abs(yDestination - yPosition) <= change)
    {
        WarpToXYDestination();
        atDestination = true;
    }
}

void Actor::SetAction(int which_action)
{
    if (action != which_action)
    {
        SetCurrentFrame(0);
        SetCurrentFrameDelay(0);
    }

    action = which_action;

    if (hasAnimations)
    {
        switch (action)
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
