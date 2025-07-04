#pragma once

#include "keyboard.h"

#include "image.h"

#include "actorindex.h"
#include "actor.h"

class PC : public Actor
{
    int stepsWalkedCount;

public:
    static PC *pc;

    PC();
    ~PC();

    void Logic();
    void Drawing();
    void Input();
};
