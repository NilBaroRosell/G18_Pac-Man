#include "Play.h"

Play::Play()
{
	state = SceneStates::RUNNING_PLAY;
}

void Play::Update(bool * _keys, Vec2 _mousePosition)
{
	switch (state)
	{
		case START_GAME_PLAY:
			break;
		case RUNNING_PLAY:
			break;
		case PAUSED_PLAY:
			break;
		case GAME_OVER_PLAY:
			break;
		default:
			break;
	}
}

void Play::Draw()
{
	std::cout << "DRAWING PLAY" << std::endl;
}


Play::~Play()
{
}
