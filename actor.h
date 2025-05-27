#pragma once

#include "tile.h"

#include "actorindex.h"

#include "area.h"

#include <iostream>

class Actor
{
    bool isActive{};

    float xPosition{}, yPosition{};
    float drawXPosition{}, drawYPosition{};
    int xCell{}, yCell{};

    bool atDestination{};
    float xDestination{}, yDestination{};

    int facing{};

    float moveSpeed{};

    int action{};

    int spriteID{};

    bool hasAnimations{};
    int currentFrame{}, numFrames{};
    int currentFrameDelay{}, maxFrameDelay{};

public:
    Actor();
    ~Actor();

    void Logic();
    void Drawing();

    void Face(int direction);
    void Walk(int direction);
    void Stand();

    bool GetIsActive() const { return isActive; }
    void SetIsActive(bool active){isActive = active;}

    float GetXPosition()const{return xPosition;}
    float GetYPosition()const{return yPosition;}
    void SetXPosition(float x){xPosition = x;}
    void SetYPosition(float y){yPosition = y;}
    void SetXYPosition(float x, float y)
    {
        SetXPosition(x);
        SetYPosition(y);
    }

    float GetAtDestination()const{return atDestination;}
    void SetAtDestination(bool b){atDestination = b;}
    float GetXDestination()const {return xDestination;}
    float GetYDestination()const {return yDestination;}
    void SetXDestination(float x){xDestination = x;}
    void SetYDestination(float y){yDestination = y;}
    void SetXYDestination(float x, float y)
    {
        SetXDestination(x);
        SetYDestination(y);
    }
    void WarpToXDestination(){SetXPosition(xDestination);}
    void WarpToYDestination(){SetYPosition(yDestination);}
    void WarpToXYDestination()
    {
        WarpToXDestination();
        WarpToYDestination();
    }

    void ApproachDestinationLinear(float change);
    void ApproachDestinationFractional(float change);

    float GetDrawXPosition()const{return drawXPosition;}
    float GetDrawYPosition()const{return drawYPosition;}
    void SetDrawXPosition(float x){drawXPosition = x;}
    void SetDrawYPosition(float y){drawYPosition = y;}
    void SetDrawXYPosition(float x, float y)
    {
        SetDrawXPosition(x);
        SetDrawYPosition(y);
    }

    int GetXCell()const{return xCell;}
    int GetYCell()const{return yCell;}
    void SetXCell(int x, bool warp_to_dest)
    {
        xCell = x;
        SetXDestination(xCell * Tile::WIDTH);
        if(warp_to_dest)
            WarpToXDestination();
    }
    void SetYCell(int y, bool warp_to_dest)
    {
        yCell = y;
        SetYDestination(yCell * Tile::HEIGHT);
        if(warp_to_dest)
            WarpToYDestination();
    }
    void SetXYCell(int x, int y, bool warp_to_dest)
    {
        SetXCell(x, warp_to_dest);
        SetYCell(y, warp_to_dest);
    }

    int GetFacing()const{return facing;}

    float GetMoveSpeed() const { return moveSpeed; }
    void SetMoveSpeed(float speed){moveSpeed = speed;}

    int GetAction()const{return action;}
    void SetAction(int which_action);

    int GetSpriteID()const{return spriteID;}
    void SetSpriteID(int id){spriteID = id;}

    bool GetHasAnimations()const{return hasAnimations;}
    void SetHasAnimations(bool b){hasAnimations = b;}
    int GetCurrentFrame() const {return currentFrame;}
    void SetCurrentFrame(int current_frame){currentFrame = current_frame;}
    int GetNumFrames() const {return numFrames;}
    void SetNumFrames(int num_frames){numFrames = num_frames;}
    int GetCurrentFrameDelay() const {return currentFrameDelay;}
    void SetCurrentFrameDelay(int current_frame_delay){currentFrameDelay = current_frame_delay;}
    int GetMaxFrameDelay() const {return maxFrameDelay;}
    void SetMaxFrameDelay(int max_frame_delay){maxFrameDelay = max_frame_delay;}
};

