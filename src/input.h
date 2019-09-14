#ifndef INPUT_H
#define INPUT_H

#include <array>

enum WiiButton
{
    UP = 0,
    RIGHT,
    DOWN,
    LEFT,
    A,
    B,
    ONE,
    TWO,
    LENGTH // DO NOT USE, strictly for my implementation
};

struct ButtonState
{
    bool isPressed;
    bool isHeld;
};

using InputState = std::array<ButtonState, LENGTH>;

bool controllersConnected();
InputState getButtonStates();

#endif
