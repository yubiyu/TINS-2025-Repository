#include "keyboard.h"

bool Keyboard::keyInput[NUM_INPUT_KEYS];
int Keyboard::keyHoldTicks[NUM_INPUT_KEYS];

void Keyboard::Initialize()
{
    al_install_keyboard();

    for(unsigned i = 0; i < NUM_INPUT_KEYS; i++)
    {
        keyInput[i] = false;
        keyHoldTicks[i] = 0;
    }
}

void Keyboard::Uninitialize()
{
    al_uninstall_keyboard();
}

void Keyboard::InputKeydown()
{
    switch(Event::event.keyboard.keycode)
    {
    case ALLEGRO_KEY_A:
        keyInput[KEY_A] = true;
        break;
    case ALLEGRO_KEY_B:
        keyInput[KEY_B] = true;
        break;
    case ALLEGRO_KEY_C:
        keyInput[KEY_C] = true;
        break;
    case ALLEGRO_KEY_D:
        keyInput[KEY_D] = true;
        break;
    case ALLEGRO_KEY_E:
        keyInput[KEY_E] = true;
        break;
    case ALLEGRO_KEY_F:
        keyInput[KEY_F] = true;
        break;
    case ALLEGRO_KEY_G:
        keyInput[KEY_G] = true;
        break;
    case ALLEGRO_KEY_H:
        keyInput[KEY_H] = true;
        break;
    case ALLEGRO_KEY_I:
        keyInput[KEY_I] = true;
        break;
    case ALLEGRO_KEY_J:
        keyInput[KEY_J] = true;
        break;
    case ALLEGRO_KEY_K:
        keyInput[KEY_K] = true;
        break;
    case ALLEGRO_KEY_L:
        keyInput[KEY_L] = true;
        break;
    case ALLEGRO_KEY_M:
        keyInput[KEY_M] = true;
        break;
    case ALLEGRO_KEY_N:
        keyInput[KEY_N] = true;
        break;
    case ALLEGRO_KEY_O:
        keyInput[KEY_O] = true;
        break;
    case ALLEGRO_KEY_P:
        keyInput[KEY_P] = true;
        break;
    case ALLEGRO_KEY_Q:
        keyInput[KEY_Q] = true;
        break;
    case ALLEGRO_KEY_R:
        keyInput[KEY_R] = true;
        break;
    case ALLEGRO_KEY_S:
        keyInput[KEY_S] = true;
        break;
    case ALLEGRO_KEY_T:
        keyInput[KEY_T] = true;
        break;
    case ALLEGRO_KEY_U:
        keyInput[KEY_U] = true;
        break;
    case ALLEGRO_KEY_V:
        keyInput[KEY_V] = true;
        break;
    case ALLEGRO_KEY_W:
        keyInput[KEY_W] = true;
        break;
    case ALLEGRO_KEY_X:
        keyInput[KEY_X] = true;
        break;
    case ALLEGRO_KEY_Y:
        keyInput[KEY_Y] = true;
        break;
    case ALLEGRO_KEY_Z:
        keyInput[KEY_Z] = true;
        break;
    case ALLEGRO_KEY_PAD_1:
        keyInput[KEY_PAD_1] = true;
        break;
    case ALLEGRO_KEY_PAD_2:
        keyInput[KEY_PAD_2] = true;
        break;
    case ALLEGRO_KEY_PAD_3:
        keyInput[KEY_PAD_3] = true;
        break;
    case ALLEGRO_KEY_PAD_4:
        keyInput[KEY_PAD_4] = true;
        break;
    case ALLEGRO_KEY_PAD_5:
        keyInput[KEY_PAD_5] = true;
        break;
    case ALLEGRO_KEY_PAD_6:
        keyInput[KEY_PAD_6] = true;
        break;
    case ALLEGRO_KEY_PAD_7:
        keyInput[KEY_PAD_7] = true;
        break;
    case ALLEGRO_KEY_PAD_8:
        keyInput[KEY_PAD_8] = true;
        break;
    case ALLEGRO_KEY_PAD_9:
        keyInput[KEY_PAD_9] = true;
        break;
    case ALLEGRO_KEY_PAD_0:
        keyInput[KEY_PAD_0] = true;
        break;
    case ALLEGRO_KEY_1:
        keyInput[KEY_1] = true;
        break;
    case ALLEGRO_KEY_2:
        keyInput[KEY_2] = true;
        break;
    case ALLEGRO_KEY_3:
        keyInput[KEY_3] = true;
        break;
    case ALLEGRO_KEY_4:
        keyInput[KEY_4] = true;
        break;
    case ALLEGRO_KEY_5:
        keyInput[KEY_5] = true;
        break;
    case ALLEGRO_KEY_6:
        keyInput[KEY_6] = true;
        break;
    case ALLEGRO_KEY_7:
        keyInput[KEY_7] = true;
        break;
    case ALLEGRO_KEY_8:
        keyInput[KEY_8] = true;
        break;
    case ALLEGRO_KEY_9:
        keyInput[KEY_9] = true;
        break;
    case ALLEGRO_KEY_0:
        keyInput[KEY_0] = true;
        break;
    case ALLEGRO_KEY_UP:
        keyInput[KEY_UP] = true;
        break;
    case ALLEGRO_KEY_DOWN:
        keyInput[KEY_DOWN] = true;
        break;
    case ALLEGRO_KEY_LEFT:
        keyInput[KEY_LEFT] = true;
        break;
    case ALLEGRO_KEY_RIGHT:
        keyInput[KEY_RIGHT] = true;
        break;
    case ALLEGRO_KEY_SPACE:
        keyInput[KEY_SPACE] = true;
        break;
    case ALLEGRO_KEY_ENTER:
        keyInput[KEY_ENTER] = true;
        break;
    case ALLEGRO_KEY_LSHIFT:
        keyInput[KEY_LSHIFT] = true;
        break;
    case ALLEGRO_KEY_RSHIFT:
        keyInput[KEY_RSHIFT] = true;
        break;
    case ALLEGRO_KEY_ESCAPE:
        keyInput[KEY_ESC] = true;
        break;
    }
}

void Keyboard::InputKeyup()
{
    switch(Event::event.keyboard.keycode)
    {
    case ALLEGRO_KEY_A:
        keyInput[KEY_A] = false;
        keyHoldTicks[KEY_A] = 0;
        break;
    case ALLEGRO_KEY_B:
        keyInput[KEY_B] = false;
        keyHoldTicks[KEY_B] = 0;
        break;
    case ALLEGRO_KEY_C:
        keyInput[KEY_C] = false;
        keyHoldTicks[KEY_C] = 0;
        break;
    case ALLEGRO_KEY_D:
        keyInput[KEY_D] = false;
        keyHoldTicks[KEY_D] = 0;
        break;
    case ALLEGRO_KEY_E:
        keyInput[KEY_E] = false;
        keyHoldTicks[KEY_E] = 0;
        break;
    case ALLEGRO_KEY_F:
        keyInput[KEY_F] = false;
        keyHoldTicks[KEY_F] = 0;
        break;
    case ALLEGRO_KEY_G:
        keyInput[KEY_G] = false;
        keyHoldTicks[KEY_G] = 0;
        break;
    case ALLEGRO_KEY_H:
        keyInput[KEY_H] = false;
        keyHoldTicks[KEY_H] = 0;
        break;
    case ALLEGRO_KEY_I:
        keyInput[KEY_I] = false;
        keyHoldTicks[KEY_I] = 0;
        break;
    case ALLEGRO_KEY_J:
        keyInput[KEY_J] = false;
        keyHoldTicks[KEY_J] = 0;
        break;
    case ALLEGRO_KEY_K:
        keyInput[KEY_K] = false;
        keyHoldTicks[KEY_K] = 0;
        break;
    case ALLEGRO_KEY_L:
        keyInput[KEY_L] = false;
        keyHoldTicks[KEY_L] = 0;
        break;
    case ALLEGRO_KEY_M:
        keyInput[KEY_M] = false;
        keyHoldTicks[KEY_M] = 0;
        break;
    case ALLEGRO_KEY_N:
        keyInput[KEY_N] = false;
        keyHoldTicks[KEY_N] = 0;
        break;
    case ALLEGRO_KEY_O:
        keyInput[KEY_O] = false;
        keyHoldTicks[KEY_O] = 0;
        break;
    case ALLEGRO_KEY_P:
        keyInput[KEY_P] = false;
        keyHoldTicks[KEY_P] = 0;
        break;
    case ALLEGRO_KEY_Q:
        keyInput[KEY_Q] = false;
        keyHoldTicks[KEY_Q] = 0;
        break;
    case ALLEGRO_KEY_R:
        keyInput[KEY_R] = false;
        keyHoldTicks[KEY_R] = 0;
        break;
    case ALLEGRO_KEY_S:
        keyInput[KEY_S] = false;
        keyHoldTicks[KEY_S] = 0;
        break;
    case ALLEGRO_KEY_T:
        keyInput[KEY_T] = false;
        keyHoldTicks[KEY_T] = 0;
        break;
    case ALLEGRO_KEY_U:
        keyInput[KEY_U] = false;
        keyHoldTicks[KEY_U] = 0;
        break;
    case ALLEGRO_KEY_V:
        keyInput[KEY_V] = false;
        keyHoldTicks[KEY_V] = 0;
        break;
    case ALLEGRO_KEY_W:
        keyInput[KEY_W] = false;
        keyHoldTicks[KEY_W] = 0;
        break;
    case ALLEGRO_KEY_X:
        keyInput[KEY_X] = false;
        keyHoldTicks[KEY_X] = 0;
        break;
    case ALLEGRO_KEY_Y:
        keyInput[KEY_Y] = false;
        keyHoldTicks[KEY_Y] = 0;
        break;
    case ALLEGRO_KEY_Z:
        keyInput[KEY_Z] = false;
        keyHoldTicks[KEY_Z] = 0;
        break;
    case ALLEGRO_KEY_PAD_1:
        keyInput[KEY_PAD_1] = false;
        keyHoldTicks[KEY_PAD_1] = 0;
        break;
    case ALLEGRO_KEY_PAD_2:
        keyInput[KEY_PAD_2] = false;
        keyHoldTicks[KEY_PAD_2] = 0;
        break;
    case ALLEGRO_KEY_PAD_3:
        keyInput[KEY_PAD_3] = false;
        keyHoldTicks[KEY_PAD_3] = 0;
        break;
    case ALLEGRO_KEY_PAD_4:
        keyInput[KEY_PAD_4] = false;
        keyHoldTicks[KEY_PAD_4] = 0;
        break;
    case ALLEGRO_KEY_PAD_5:
        keyInput[KEY_PAD_5] = false;
        keyHoldTicks[KEY_PAD_5] = 0;
        break;
    case ALLEGRO_KEY_PAD_6:
        keyInput[KEY_PAD_6] = false;
        keyHoldTicks[KEY_PAD_6] = 0;
        break;
    case ALLEGRO_KEY_PAD_7:
        keyInput[KEY_PAD_7] = false;
        keyHoldTicks[KEY_PAD_7] = 0;
        break;
    case ALLEGRO_KEY_PAD_8:
        keyInput[KEY_PAD_8] = false;
        keyHoldTicks[KEY_PAD_8] = 0;
        break;
    case ALLEGRO_KEY_PAD_9:
        keyInput[KEY_PAD_9] = false;
        keyHoldTicks[KEY_PAD_9] = 0;
        break;
    case ALLEGRO_KEY_PAD_0:
        keyInput[KEY_PAD_0] = false;
        keyHoldTicks[KEY_PAD_0] = 0;
        break;
    case ALLEGRO_KEY_1:
        keyInput[KEY_1] = false;
        keyHoldTicks[KEY_1] = 0;
        break;
    case ALLEGRO_KEY_2:
        keyInput[KEY_2] = false;
        keyHoldTicks[KEY_2] = 0;
        break;
    case ALLEGRO_KEY_3:
        keyInput[KEY_3] = false;
        keyHoldTicks[KEY_3] = 0;
        break;
    case ALLEGRO_KEY_4:
        keyInput[KEY_4] = false;
        keyHoldTicks[KEY_4] = 0;
        break;
    case ALLEGRO_KEY_5:
        keyInput[KEY_5] = false;
        keyHoldTicks[KEY_5] = 0;
        break;
    case ALLEGRO_KEY_6:
        keyInput[KEY_6] = false;
        keyHoldTicks[KEY_6] = 0;
        break;
    case ALLEGRO_KEY_7:
        keyInput[KEY_7] = false;
        keyHoldTicks[KEY_7] = 0;
        break;
    case ALLEGRO_KEY_8:
        keyInput[KEY_8] = false;
        keyHoldTicks[KEY_8] = 0;
        break;
    case ALLEGRO_KEY_9:
        keyInput[KEY_9] = false;
        keyHoldTicks[KEY_9] = 0;
        break;
    case ALLEGRO_KEY_0:
        keyInput[KEY_0] = false;
        keyHoldTicks[KEY_0] = 0;
        break;
    case ALLEGRO_KEY_UP:
        keyInput[KEY_UP] = false;
        keyHoldTicks[KEY_UP] = 0;
        break;
    case ALLEGRO_KEY_DOWN:
        keyInput[KEY_DOWN] = false;
        keyHoldTicks[KEY_DOWN] = 0;
        break;
    case ALLEGRO_KEY_LEFT:
        keyInput[KEY_LEFT] = false;
        keyHoldTicks[KEY_LEFT] = 0;
        break;
    case ALLEGRO_KEY_RIGHT:
        keyInput[KEY_RIGHT] = false;
        keyHoldTicks[KEY_RIGHT] = 0;
        break;
    case ALLEGRO_KEY_SPACE:
        keyInput[KEY_SPACE] = false;
        keyHoldTicks[KEY_SPACE] = 0;
        break;
    case ALLEGRO_KEY_ENTER:
        keyInput[KEY_ENTER] = false;
        keyHoldTicks[KEY_ENTER] = 0;
        break;
    case ALLEGRO_KEY_LSHIFT:
        keyInput[KEY_LSHIFT] = false;
        keyHoldTicks[KEY_LSHIFT] = 0;
        break;
    case ALLEGRO_KEY_RSHIFT:
        keyInput[KEY_RSHIFT] = false;
        keyHoldTicks[KEY_RSHIFT] = 0;
        break;

    case ALLEGRO_KEY_ESCAPE:
        keyInput[KEY_ESC] = false;
        keyHoldTicks[KEY_ESC] = 0;
        break;
    }
}

void Keyboard::InputKeyHold()
{
    for(unsigned i = KEY_MARKER_FIRST; i <= KEY_MARKER_LAST; i++)
        if(keyInput[i])
            keyHoldTicks[i] ++;
}
