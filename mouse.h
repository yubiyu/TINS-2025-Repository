#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

#include "event.h"

#include "display.h"

struct Mouse
{
    static bool mouseAxesAltered; // Whether InputMouseXY() or InputMouseWheel() has been called this cycle. Reset if ALLEGRO_EVENT_MOUSE_AXES was not called.
    static float displayXPosition;
    static float displayYPosition;

    enum enumInputMouseButtons
    {
        MOUSE_NOTHING = 0, // Allegro mouse buttons start counting from 1 for some reason, so this really is just filler.

        MOUSE_LEFT = 1,
        MOUSE_RIGHT = 2,
        MOUSE_MIDDLE = 3
    };
    static const int NUM_MOUSE_BUTTONS = 4;
    static bool mouseInput[NUM_MOUSE_BUTTONS];
    static int mouseButtonHoldTicks[NUM_MOUSE_BUTTONS];

    enum enumInputMouseWheel
    {
        MOUSEWHEEL_UP = 0,
        MOUSEWHEEL_DOWN = 1
    };
    static const int NUM_MOUSEWHEEL_OPTIONS = 2;
    static bool mousewheelInput[NUM_MOUSEWHEEL_OPTIONS];


    static void Initialize();
    static void Uninitialize();

    static void InputMouseXY();
    static void InputMousewheel();
    static void InputMouseDown();
    static void InputMouseUp();

    static void InputMouseButtonHold();
};

#endif // MOUSE_H_INCLUDED
