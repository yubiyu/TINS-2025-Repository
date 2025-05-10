#pragma once

#include "input/keyboard.h"

#include "resource/image.h"

#include "world/actorindex.h"
#include "world/actor.h"


class PC : public Actor
{

public:
    static PC* pc;

    PC();
    ~PC();

    void Logic();
    void Drawing();
    void Input();
};
