#ifndef RENDER_H
#define RENDER_H

#include <array>
#include "globals.h"

struct Pixel
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

using Frame = std::array<Pixel, cols>;

void renderFrame(const Frame & frame);

#endif
