#pragma once
#include "Types.h"
#include <SDL.h>

class Inputs
{
private:
	bool keys[9];
	Vec2 mousePosition;
	SDL_Event event;
public:
	Inputs();
	bool* GetInputs();
	Vec2 GetMousePosition();
	~Inputs();
};

