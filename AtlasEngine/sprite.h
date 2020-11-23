#pragma once
#include "pch.h"

struct Sprite
{
	unsigned int texture;
	unsigned int startingVertex;
};

Sprite* Sprite_Init(const char* filename);