#pragma once
#ifndef RADLED_H
#define RADLED_H
#include <map>
#include <array>

namespace LEDGameSpace 
{
public:
	struct pixel {
		uint8_t r;
		uint8_t g;
		uint8_t b;
	};

	static pixel[][] GameFrame(std::map<std::array<ButtonState, LENGTH> map);
};

#endif