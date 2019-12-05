#include "Inputs.h"

Inputs::Inputs()
{
	for (int i = 0; i < (int)InputKey::COUNT; i++)
	{
		keys[i] = false;
	}
	mousePosition.x = 0;
	mousePosition.y = 0;
}

bool* Inputs::GetInputs()
{
	keys[(int)InputKey::K_MOUSE] = false;
	keys[(int)InputKey::K_ESC] = false;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			keys[(int)InputKey::K_ESC] = true;
			break;
		case SDL_KEYDOWN:
			keys[(int)InputKey::K_ESC] = event.key.keysym.sym == SDLK_ESCAPE;
			keys[(int)InputKey::K_SPACE] = event.key.keysym.sym == SDLK_SPACE;
			keys[(int)InputKey::K_P] = event.key.keysym.sym == SDL_SCANCODE_P;
			keys[(int)InputKey::K_LEFT] = event.key.keysym.sym == SDLK_LEFT;
			keys[(int)InputKey::K_RIGHT] = event.key.keysym.sym == SDLK_RIGHT;
			keys[(int)InputKey::K_UP] = event.key.keysym.sym == SDLK_UP;
			keys[(int)InputKey::K_DOWN] = event.key.keysym.sym == SDLK_DOWN;
			break;
		case SDL_MOUSEBUTTONUP:
			keys[(int)InputKey::K_MOUSE] = true;
			break;
		default:;
		}
	}

	return keys;
}

Vec2 Inputs::GetMousePosition()
{
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_MOUSEMOTION:
				mousePosition.x = event.motion.x;
				mousePosition.y = event.motion.y;
				break;
			default: break;
		}
	}
	return mousePosition;
}

Inputs::~Inputs()
{
}
