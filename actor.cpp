#include "actor.h"

Actor::Actor()
{
    isActive = true;

    atDestination = true;

    facing = Direction::DOWN;
    moveSpeed = ActorIndex::WALK_SPEED_BASE;

    SetAction(ActorIndex::ACTION_STAND);

    stepsWalkedCount = 0;
}

Actor::~Actor()
{
}

void Actor::Logic()
{

    if (!atDestination)
    {
        ApproachDestinationLinear(moveSpeed);
        if (atDestination) // Reached destination
        {
            if (Area::VoidCellCheck(roomXCell, roomYCell))
            {
                InitiateDescendLayer();
            }
            else if (Area::TeleporterCellCheck(roomXCell, roomYCell))
            {
                /// Todo: The case where an actor lands on a teleporter after teleporting.
                /// Todo: The case where an actor lands on a teleporter after teleporting, but its next move is blocked by an obstacle, triggering the teleporter without changing cell.
                InitiateAscendLayer();
            }
        }
    }
    else // atDestination
    {
        // Code for actor falling multiple layers back to back.
        if (!Area::inRoomTransition)
        {
            if (Area::VoidCellCheck(roomXCell, roomYCell))
            {
                if (consecutiveDescents > MAX_CONSECUTIVE_DESCENTS)
                {
                    SetRoomXYCell(Area::roomSpawnCol, Area::roomSpawnRow, true);
                    consecutiveDescents = 0;
                }
                else
                {
                    InitiateDescendLayer();
                    consecutiveDescents++;
                }
            }
            else
                consecutiveDescents = 0;
        }
    }

    if (inPreAscension)
    {
        preAscensionDrawingYOffset += PRE_ASCENSION_EFFECT_Y_SPEED;

        ascensionSpinDelay++;
        if (ascensionSpinDelay >= ASCENSION_SPIN_MAX_DELAY)
        {
            ascensionSpinDelay = 0;
            RotateFacing();
        }

        preAscensionDelay++;
        if (preAscensionDelay >= maxPreAscensionDelay)
        {
            inPreAscension = false;

            if (Area::winConditionInitiated)
            {
                Area::winConditionAchieved = true;
            }
            else
                SetWorldYCell(Area::worldGridCurrentRow * Area::ROOM_ROWS + GetRoomYCell(), true);
        }
    }

    if (inPreDescension)
    {
        preDescensionDrawingYOffset += PRE_DESCENSION_EFFECT_Y_SPEED;

        preDescensionDelay++;
        if (preDescensionDelay >= maxPreDescensionDelay)
        {
            inPreDescension = false;
            SetWorldYCell(Area::worldGridCurrentRow * Area::ROOM_ROWS + GetRoomYCell(), true);
            // WarpToXYDestination();
        }
    }

    /// BEGIN DRAWING RELATED LOGIC

    drawingXOffset = 0;

    drawingYOffset = 0;
    if (inPreAscension)
        drawingYOffset += preAscensionDrawingYOffset;
    if (inPreDescension)
        drawingYOffset += preDescensionDrawingYOffset;

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
    /// END DRAWING RELATED LOGIC
}

void Actor::Face(int direction)
{
    if (atDestination)
        facing = direction;
}

void Actor::Walk(int direction)
{
    Face(direction);

    if (atDestination)
    {
        atDestination = false;

        SetAction(ActorIndex::ACTION_WALK);

        bool collidedWithObstacle = false;

        switch (facing)
        {
        case Direction::UP:
            if (!Area::RoomBoundaryCheck(roomXCell, roomYCell - 1))
            {
                if (!Area::WalkObstacleCheck(roomXCell, roomYCell - 1))
                    SetRoomYCell(roomYCell - 1, false);
                else
                    collidedWithObstacle = true;
            }
            else if (Area::adjacentRooms[Direction::UP] != Area::VOID_ROOM_ID)
            {
                /// Todo: Ensure only PC actor can trigger a room change.
                Area::ChangeRoom(Area::worldGridCurrentCol, Area::worldGridCurrentRow - 1, Area::ROOM_TRANSITION_TRANSLATION);
                SetWorldYCell(worldYCell - 1, true);
            }
            break;

        case Direction::DOWN:
            if (!Area::RoomBoundaryCheck(roomXCell, roomYCell + 1))
            {
                if (!Area::WalkObstacleCheck(roomXCell, roomYCell + 1))
                    SetRoomYCell(roomYCell + 1, false);
                else
                    collidedWithObstacle = true;
            }
            else if (Area::adjacentRooms[Direction::DOWN] != Area::VOID_ROOM_ID)
            {
                Area::ChangeRoom(Area::worldGridCurrentCol, Area::worldGridCurrentRow + 1, Area::ROOM_TRANSITION_TRANSLATION);
                SetWorldYCell(worldYCell + 1, true);
            }
            break;

        case Direction::LEFT:
            if (!Area::RoomBoundaryCheck(roomXCell - 1, roomYCell))
            {
                if (!Area::WalkObstacleCheck(roomXCell - 1, roomYCell))
                    SetRoomXCell(roomXCell - 1, false);
                else
                    collidedWithObstacle = true;
            }
            else if (Area::adjacentRooms[Direction::LEFT] != Area::VOID_ROOM_ID)
            {
                Area::ChangeRoom(Area::worldGridCurrentCol - 1, Area::worldGridCurrentRow, Area::ROOM_TRANSITION_TRANSLATION);
                SetWorldXCell(worldXCell - 1, true);
            }
            break;

        case Direction::RIGHT:
            if (!Area::RoomBoundaryCheck(roomXCell + 1, roomYCell))
            {
                if (!Area::WalkObstacleCheck(roomXCell + 1, roomYCell))
                    SetRoomXCell(roomXCell + 1, false);
                else
                    collidedWithObstacle = true;
            }
            else if (Area::adjacentRooms[Direction::RIGHT] != Area::VOID_ROOM_ID)
            {
                Area::ChangeRoom(Area::worldGridCurrentCol + 1, Area::worldGridCurrentRow, Area::ROOM_TRANSITION_TRANSLATION);
                SetWorldXCell(worldXCell + 1, true);
            }
            break;
        }

        if (isPC && !collidedWithObstacle)
        {
            FoodEater::ProgressNutrition(1);
            if(FoodEater::nutrition <= 0)
                Area::loseConditionAchieved = true;

            stepsWalkedCount ++;
            //std::cout << "Steps walked: " << GetStepsWalkedCount() << std::endl;
        }
    }
}

void Actor::Stand()
{
    if (atDestination)
        SetAction(ActorIndex::ACTION_STAND);
}

void Actor::InitiateAscendLayer()
{

    inPreAscension = true;
    preAscensionDelay = 0;
    maxPreAscensionDelay = Area::ROOM_TRANSITION_ASCEND_DELAY;
    preAscensionDrawingYOffset = 0;

    if (Area::winConditionInitiated && isPC)
    {
        maxPreAscensionDelay = Area::ROOM_TRANSITION_ASCEND_DELAY_WITH_WIN_CONDITION;
    }
    else
    {
        if (isPC)
            Area::AscendLayer();

        /// HAX HAX HAX HAX
        SetYPosition(Area::previousRoomYPosition + GetRoomYCell() * Tile::HEIGHT);
        FoodEater::ProgressNutrition(2);
        if(FoodEater::nutrition <= 0)
            Area::loseConditionAchieved = true;
        /// HAX HAX HAX HAX
    }
}

void Actor::InitiateDescendLayer()
{
    if (isPC)
        Area::DescendLayer();
    /// HAX HAX HAX HAX
    SetYPosition(Area::previousRoomYPosition + GetRoomYCell() * Tile::HEIGHT);
    FoodEater::ProgressNutrition(2);
    if(FoodEater::nutrition <= 0)
        Area::loseConditionAchieved = true;
    /// HAX HAX HAX HAX

    inPreDescension = true;
    preDescensionDelay = 0;
    maxPreDescensionDelay = Area::ROOM_TRANSITION_DESCEND_DELAY;
    preDescensionDrawingYOffset = 0;
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
