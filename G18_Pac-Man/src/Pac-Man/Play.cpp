#include "Play.h"

Play::Play()
{
	ReadConfig();
	state = SceneStates::RUNNING_PLAY;
}

void Play::ReadConfig()
{
	/*wall.objectId = PACMAN_SPRITESHEET::ID;
	wall.objectRect.x = SCREEN_HEIGHT;
	wall.objectRect.y = INITIAL_Y;
	wall.objectRect.w = GAME_SPRITES_SIZE;
	wall.objectRect.h = GAME_SPRITES_SIZE;
	wall.objectSpriteRect.x = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).x / 8) * 7;4
	wall.objectSpriteRect.y = (Renderer::Instance()->GetTextureSize(PACMAN_SPRITESHEET::ID).y / 8) * 6;
	wall.objectSpriteRect.w = 128;
	wall.objectSpriteRect.h = 128;*/
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
	Renderer::Instance()->SetRendreDrawColor(0, 0, 0);
	Renderer::Instance()->Clear();
	background.Draw();
	Renderer::Instance()->Render();
}


Play::~Play()
{
}
