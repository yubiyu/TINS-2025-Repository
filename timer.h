#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <allegro5/allegro5.h>

struct Timer
{
    static ALLEGRO_TIMER*FPSTimer;

    static constexpr float FPS = 60.0; // Governs the speed and period of things other than just redrawing speed, so be careful about changing FPS

    static void Initialize();
    static void Uninitialize();

};

#endif // TIMER_H_INCLUDED
