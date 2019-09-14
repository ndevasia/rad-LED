#ifndef INPUT_H
#define INPUT_H

#include <map>

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

bool controllersConnected();
std::array<ButtonState, LENGTH> getButtonStates();

#endif
