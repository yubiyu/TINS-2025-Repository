#pragma once

#include "keyboard.h"

#include "image.h"

#include "actorindex.h"
#include "actor.h"

class PC : public Actor
{
    int ascensionSpinFrame {};
    int facingWithAscensionSpin {};
    int ascensionSpinFrameDelay {};
    const int ASCENSION_SPIN_MAX_FRAME_DELAY = Timer::FPS * 0.1;

public:
    static PC *pc;

    PC();
    ~PC();

    void Logic();
    void Drawing();
    void Input();
};
