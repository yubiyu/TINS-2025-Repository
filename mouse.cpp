#include "mouse.h"


bool Mouse::mouseAxesAltered = false;
float Mouse::displayXPosition;
float Mouse::displayYPosition;

bool Mouse::mouseInput[NUM_MOUSE_BUTTONS];
int Mouse::mouseButtonHoldTicks[NUM_MOUSE_BUTTONS];

bool Mouse::mousewheelInput[NUM_MOUSEWHEEL_OPTIONS];

void Mouse::Initialize()
{
    al_install_mouse();
    //al_hide_mouse_cursor(Display::display);

    for(int i = 0; i < NUM_MOUSE_BUTTONS; i++)
    {
        mouseInput[i] = false;
        mouseButtonHoldTicks[i] = 0;
    }

    for(int i = 0; i < NUM_MOUSEWHEEL_OPTIONS; i++)
        mousewheelInput[i] = false;
}

void Mouse::Uninitialize()
{
    al_uninstall_mouse();
}

void Mouse::InputMouseXY()
{
    mouseAxesAltered = true;
    displayXPosition = Event::event.mouse.x;
    displayYPosition = Event::event.mouse.y;
}

void Mouse::InputMousewheel()
{
    mouseAxesAltered = true;

    if(Event::event.mouse.z > 0)
        mousewheelInput[MOUSEWHEEL_UP] = true;
    else
        mousewheelInput[MOUSEWHEEL_UP] = false;

    if(Event::event.mouse.z < 0)
        mousewheelInput[MOUSEWHEEL_DOWN] = true;
    else
        mousewheelInput[MOUSEWHEEL_DOWN] = false;
}

void Mouse::InputMouseDown()
{
    switch(Event::event.mouse.button)
    {
    case MOUSE_LEFT:
        mouseInput[MOUSE_LEFT] = true;
        break;
    case MOUSE_RIGHT:
        mouseInput[MOUSE_RIGHT] = true;
        break;
    case MOUSE_MIDDLE:
        mouseInput[MOUSE_MIDDLE] = true;
        break;
    }
}

void Mouse::InputMouseUp()
{
    switch(Event::event.mouse.button)
    {
    case MOUSE_LEFT:
        mouseInput[MOUSE_LEFT] = false;
        mouseButtonHoldTicks[MOUSE_LEFT] = 0;
        break;
    case MOUSE_RIGHT:
        mouseInput[MOUSE_RIGHT] = false;
        mouseButtonHoldTicks[MOUSE_RIGHT] = 0;
        break;
    case MOUSE_MIDDLE:
        mouseInput[MOUSE_MIDDLE] = false;
        mouseButtonHoldTicks[MOUSE_MIDDLE] = 0;
        break;
    }
}

void Mouse::InputMouseButtonHold()
{
    if(mouseInput[MOUSE_LEFT])
        mouseButtonHoldTicks[MOUSE_LEFT] ++;
    if(mouseInput[MOUSE_RIGHT])
        mouseButtonHoldTicks[MOUSE_RIGHT] ++;
    if(mouseInput[MOUSE_MIDDLE])
        mouseButtonHoldTicks[MOUSE_MIDDLE] ++;
}
