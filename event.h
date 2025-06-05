#pragma once

#include <allegro5/allegro5.h>

#include "display.h"
#include "timer.h"

struct Event
{
    static ALLEGRO_EVENT_QUEUE *eventQueue;
    static ALLEGRO_EVENT event;

    static void Initialize();
    static void Uninitialize();
};
