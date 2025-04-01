#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#include "event.h"

struct Keyboard
{
    enum enumInputKeys
    {
        KEY_A = 0,  KEY_B = 1,  KEY_C = 2,
        KEY_D = 3,  KEY_E = 4,  KEY_F = 5,
        KEY_G = 6,  KEY_H = 7,  KEY_I = 8,
        KEY_J = 9,  KEY_K = 10, KEY_L = 11,
        KEY_M = 12, KEY_N = 13, KEY_O = 14,
        KEY_P = 15, KEY_Q = 16, KEY_R = 17,
        KEY_S = 18, KEY_T = 19, KEY_U = 20,
        KEY_V = 21, KEY_W = 22, KEY_X = 23,
        KEY_Y = 24, KEY_Z = 25,

        KEY_PAD_1 = 26, KEY_PAD_2 = 27, KEY_PAD_3 = 28,
        KEY_PAD_4 = 29, KEY_PAD_5 = 30, KEY_PAD_6 = 31,
        KEY_PAD_7 = 32, KEY_PAD_8 = 33, KEY_PAD_9 = 34,
        KEY_PAD_0 = 35,
        KEY_0 = 36, KEY_1 = 37, KEY_2 = 38, KEY_3 = 39, KEY_4 = 40,
        KEY_5 = 41, KEY_6 = 42, KEY_7 = 43, KEY_8 = 44, KEY_9 = 45,
        KEY_UP = 46, KEY_LEFT = 47, KEY_DOWN = 48, KEY_RIGHT = 49,
        KEY_SPACE = 50,
        KEY_ENTER = 51,
        KEY_LSHIFT = 52, KEY_RSHIFT = 53,

        KEY_ESC = 54
    };
    static const unsigned NUM_INPUT_KEYS = 55;
    static const unsigned KEY_MARKER_FIRST = KEY_A;
    static const unsigned KEY_MARKER_LAST = KEY_ESC;

    static bool keyInput[NUM_INPUT_KEYS];
    static int keyHoldTicks[NUM_INPUT_KEYS];

    static void Initialize();
    static void Uninitialize();

    static void InputKeydown();
    static void InputKeyup();

    static void InputKeyHold();

};

#endif // KEYBOARD_H_INCLUDED
