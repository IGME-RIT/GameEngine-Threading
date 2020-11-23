#pragma once
#include "pch.h"

// Some engines call this Entity,
// some call it Instance, same thing

struct Instance
{
	Sprite* sprite;

	// instance and thread are linked
	Thread* thread;

	float depth;
	float posX;
	float posY;
	float scaleX;
	float scaleY;
};

void Instance_Draw(Instance* instance);