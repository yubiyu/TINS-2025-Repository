#pragma once

#include <allegro5/allegro5.h>

#include <iostream>

struct Display
{
    static ALLEGRO_MONITOR_INFO monitorInfo;

    static ALLEGRO_DISPLAY *display;

    static ALLEGRO_BITMAP *scaleBuffer;

    static const int NATIVE_WIDTH = 160;
    static const int NATIVE_HEIGHT = 144;

    static int windowScale;
    static int width;
    static int height;

    enum enumVsyncMode
    {
        VSYNC_DRIVER = 0,
        VSYNC_ON = 1,
        VSYNC_OFF = 2
    };
    static int vsync; // 0 = Driver default, 1 = on, 2 = off.
    static const int VSYNC_MODE_FIRST = VSYNC_DRIVER;
    static const int VSYNC_MODE_LAST = VSYNC_OFF;

    static int fps;
    static const int FPS_MIN = 5;
    static const int FPS_MAX = 300;

    static void Initialize();
    static void Uninitialize();

    static void Resize();
    static void SetFullscreen(bool is_fullscreen);
    static void SetWindowScale(int scale);
    static void SetVsync(int vsync_mode);
    static void SetFPS(int fps_new);
};
