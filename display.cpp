#include "display.h"

ALLEGRO_MONITOR_INFO Display::monitorInfo;
ALLEGRO_DISPLAY* Display::display;

int Display::width;
int Display::height;

float Display::widthScaling;
float Display::heightScaling;

int Display::fps;

void Display::Initialize()
{
    display = al_create_display(NATIVE_WIDTH, NATIVE_HEIGHT);

    SetResolutionScaling(1);
}

void Display::Uninitialize()
{
    al_destroy_display(display);
}

void Display::SetFullscreen(bool is_fullscreen)
{
    al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, is_fullscreen);

    al_get_monitor_info(0, &monitorInfo);

    width = monitorInfo.x2 - monitorInfo.x1;
    height = monitorInfo.y2 - monitorInfo.y1;

    widthScaling = width / NATIVE_WIDTH;
    heightScaling = height / NATIVE_HEIGHT;
}

void Display::SetResolutionScaling(int scale)
{
    width = NATIVE_WIDTH * scale;
    height = NATIVE_HEIGHT * scale;

    widthScaling = width / NATIVE_WIDTH;
    heightScaling = height / NATIVE_HEIGHT;

    al_resize_display(display, width, height);
}

void Display::SetVsync(int vsync_mode)
{
    if(vsync_mode >= VSYNC_MODE_FIRST && vsync_mode <= VSYNC_MODE_LAST)
    {
        al_set_display_option(display, ALLEGRO_VSYNC, vsync_mode);
        std::cout << "Vsync mode set to " << al_get_display_option(display, ALLEGRO_VSYNC) << std::endl;
    }
}

void Display::SetFPS(int set_fps)
{
    if(set_fps >= FPS_MIN && set_fps <= FPS_MAX)
    {
        fps = set_fps;
        std::cout << "Fps set to " << set_fps << std::endl;
    }

}
