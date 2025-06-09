#pragma once

#include "settings.h"

#include "camera.h"

#include "tile.h"

#include "actorindex.h"

#include "area.h"

#include <iostream>

class Actor
{
    bool isActive{};
    bool isPC{};

    float xPosition{}, yPosition{};
    float drawingXOffset{}, drawingYOffset{};
    float preAscensionDrawingYOffset{};
    float preDescensionDrawingYOffset{};

    int worldXCell{}, worldYCell{};
    int previousWorldXCell{}, previousWorldYCell{};
    bool hasChangedWorldCell{};

    int roomXCell{}, roomYCell{};

    bool atDestination{};
    float xDestination{}, yDestination{};

    int facing{};

    float moveSpeed{};

    int action{};

    int spriteID{};

    bool hasAnimations{};
    int currentFrame{}, numFrames{};
    int currentFrameDelay{}, maxFrameDelay{};

    int ascensionSpinDelay{};
    const int ASCENSION_SPIN_MAX_DELAY = Timer::FPS * 0.1;

    bool inPreAscension{}; // Ascension translation
    int preAscensionDelay{}, maxPreAscensionDelay{};
    const float PRE_ASCENSION_EFFECT_Y_SPEED = ActorIndex::WALK_SPEED_BASE * (-2);

    bool inPreDescension{}; // Falling animation/translation
    int preDescensionDelay{}, maxPreDescensionDelay{};
    const float PRE_DESCENSION_EFFECT_Y_SPEED = ActorIndex::WALK_SPEED_BASE * 2;

    int consecutiveDescents{};
    const int MAX_CONSECUTIVE_DESCENTS = 2;

    int stepsWalkedCount{};

public:
    Actor();
    ~Actor();

    void Logic();
    void Drawing();

    void Face(int direction);
    void Walk(int direction);
    void Stand();
    void InitiateAscendLayer();
    void InitiateDescendLayer();

    bool GetIsActive() const { return isActive; }
    void SetIsActive(bool active) { isActive = active; }

    void SetIsPC(bool is_pc) { isPC = is_pc; }

    float GetXPosition() const { return xPosition; }
    float GetYPosition() const { return yPosition; }
    void SetXPosition(float x) { xPosition = x; }
    void SetYPosition(float y) { yPosition = y; }
    void SetXYPosition(float x, float y)
    {
        SetXPosition(x);
        SetYPosition(y);
    }

    float GetDrawingXOffset() const { return drawingXOffset; }
    float GetDrawingYOffset() const { return drawingYOffset; }
    void SetDrawingXOffset(float x) { drawingXOffset = x; }
    void SetDrawingYOffset(float y) { drawingYOffset = y; }
    void SetDrawingXYOffset(float x, float y)
    {
        SetDrawingXOffset(x);
        SetDrawingYOffset(y);
    }
    /*
    float GetPreviousRoomXPosition() const {return previousRoomXPosition;}
    float GetPreviousRoomYPosition() const {return previousRoomYPosition;}
    void SetPreviousRoomXPosition(float x) {previousRoomXPosition = x;}
    void SetPreviousRoomYPosition(float y){previousRoomYPosition = y;}
    void SetPreviousRoomXYPosition(float x, float y)
    {
        SetPreviousRoomXPosition(x);
        SetPreviousRoomYPosition(y);
    }
        */

    float GetAtDestination() const { return atDestination; }
    void SetAtDestination(bool b) { atDestination = b; }
    float GetXDestination() const { return xDestination; }
    float GetYDestination() const { return yDestination; }
    void SetXDestination(float x) { xDestination = x; }
    void SetYDestination(float y) { yDestination = y; }
    void SetXYDestination(float x, float y)
    {
        SetXDestination(x);
        SetYDestination(y);
    }
    void WarpToXDestination() { SetXPosition(xDestination); }
    void WarpToYDestination() { SetYPosition(yDestination); }
    void WarpToXYDestination()
    {
        WarpToXDestination();
        WarpToYDestination();
    }

    void ApproachDestinationLinear(float change);
    void ApproachDestinationFractional(float change);

    /*
    float GetDrawXPosition()const{return drawXPosition;}
    float GetDrawYPosition()const{return drawYPosition;}
    void SetDrawXPosition(float x){drawXPosition = x;}
    void SetDrawYPosition(float y){drawYPosition = y;}
    void SetDrawXYPosition(float x, float y)
    {
        SetDrawXPosition(x);
        SetDrawYPosition(y);
    }
        */

    int GetWorldXCell() const { return worldXCell; }
    int GetWorldYCell() const { return worldYCell; }
    void SetWorldXCell(int x, bool warp_to_dest)
    {
        if (x != worldXCell)
        {
            previousWorldXCell = worldXCell;
            worldXCell = x;
            roomXCell = worldXCell % Area::ROOM_COLS;
            SetXDestination(worldXCell * Tile::WIDTH);

            if (warp_to_dest)
                WarpToXDestination();
        }
    }
    void SetWorldYCell(int y, bool warp_to_dest)
    {
        if (y != worldYCell)
        {
            previousWorldYCell = worldYCell;
            worldYCell = y;
            roomYCell = worldYCell % Area::ROOM_ROWS;
            SetYDestination(worldYCell * Tile::HEIGHT);

            if (warp_to_dest)
                WarpToYDestination();
        }
    }
    void SetWorldXYCell(int x, int y, bool warp_to_dest)
    {
        SetWorldXCell(x, warp_to_dest);
        SetWorldYCell(y, warp_to_dest);
    }

    int GetRoomXCell() const { return roomXCell; }
    int GetRoomYCell() const { return roomYCell; }
    void SetRoomXCell(int x, bool warp_to_dest)
    {
        if(x != roomXCell)
        {
            roomXCell = x;
            SetWorldXCell(Area::worldGridCurrentCol * Area::ROOM_COLS + roomXCell, warp_to_dest);
            SetXDestination(worldXCell * Tile::WIDTH);
            if (warp_to_dest)
                WarpToXDestination();
        }
    }
    void SetRoomYCell(int y, bool warp_to_dest)
    {
        if(y != roomYCell)
        {
            roomYCell = y;
            SetWorldYCell(Area::worldGridCurrentRow * Area::ROOM_ROWS + roomYCell, warp_to_dest);
            SetYDestination(worldYCell * Tile::HEIGHT);
            if (warp_to_dest)
                WarpToYDestination();
        }
    }
    void SetRoomXYCell(int x, int y, bool warp_to_dest)
    {
        SetRoomXCell(x, warp_to_dest);
        SetRoomYCell(y, warp_to_dest);
    }

    int GetFacing() const { return facing; }
    void RotateFacing()
    {
        facing++;
        if (facing >= Direction::NUM_DIRECTIONS)
            facing = 0;
    }

    float GetMoveSpeed() const { return moveSpeed; }
    void SetMoveSpeed(float speed) { moveSpeed = speed; }

    int GetAction() const { return action; }
    void SetAction(int which_action);

    int GetSpriteID() const { return spriteID; }
    void SetSpriteID(int id) { spriteID = id; }

    bool GetHasAnimations() const { return hasAnimations; }
    void SetHasAnimations(bool b) { hasAnimations = b; }
    int GetCurrentFrame() const { return currentFrame; }
    void SetCurrentFrame(int current_frame) { currentFrame = current_frame; }
    int GetNumFrames() const { return numFrames; }
    void SetNumFrames(int num_frames) { numFrames = num_frames; }
    int GetCurrentFrameDelay() const { return currentFrameDelay; }
    void SetCurrentFrameDelay(int current_frame_delay) { currentFrameDelay = current_frame_delay; }
    int GetMaxFrameDelay() const { return maxFrameDelay; }
    void SetMaxFrameDelay(int max_frame_delay) { maxFrameDelay = max_frame_delay; }

    bool GetInPreDescension() const { return inPreDescension; }

    int GetStepsWalkedCount(){return stepsWalkedCount;}
};
